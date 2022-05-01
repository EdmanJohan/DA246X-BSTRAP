/**
 * @file bst.c
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "include/bst_server.h"

#include "include/configs.h"

#define SOCK_QUEUE_LEN (1U)
#define QUEUE_SIZE (2)

static kernel_pid_t announce_pid = KERNEL_PID_UNDEF;
static char announce_stack[THREAD_STACKSIZE_MEDIUM];
static msg_t announce_msg_queue[QUEUE_SIZE];

static kernel_pid_t server_main_pid = KERNEL_PID_UNDEF;
static char server_stack[THREAD_STACKSIZE_LARGE + THREAD_EXTRA_STACKSIZE_PRINTF];
static msg_t server_msg_queue[QUEUE_SIZE];

static sock_tcp_t sock_queue[SOCK_QUEUE_LEN];

extern struct curve_params cparms;
extern unsigned char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

static void* _announce(void* arg) {
    (void)arg;
    msg_init_queue(announce_msg_queue, QUEUE_SIZE);

    /* Configure local UDP endpoint */
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;

    /* Bind to global address, using predefined to operate w/o infrastructure */
    ipv6_addr_from_str((ipv6_addr_t*)&local.addr, GLOBAL_ADDR);

    if (sock_udp_create(&sock, &local, NULL, 0) != 0) {
        return (void*)1;
    }

    /* Configure remote UDP endpoint */
    sock_udp_ep_t remote = {.family = AF_INET6};
    remote.port = MULTICAST_PORT;
    ipv6_addr_set_all_nodes_multicast((ipv6_addr_t*)&remote.addr.ipv6, IPV6_ADDR_MCAST_SCP_LINK_LOCAL);

    msg_t msg;
    while (1) {
        if (msg_try_receive(&msg) == 1) {
            if (msg.content.value == MSG_ACTION_STOP) {
                sock_udp_close(&sock);

                msg_t reply;
                reply.content.value = msg.content.value & 0x0;
                msg_reply(&msg, &reply);
                thread_zombify();
            }
        }

        sock_udp_send(&sock, &MSG_ANNOUNCE, sizeof(MSG_ANNOUNCE), &remote);
        xtimer_sleep(10);
    }

    /* Should never be reached */
    return NULL;
}

static void* _server_encrypted_thread(void* arg) {
    (void)arg;
    msg_init_queue(server_msg_queue, QUEUE_SIZE);

    uint8_t buf[128];
    sock_tcp_queue_t queue;
    sock_tcp_ep_t local = SOCK_IPV6_EP_ANY;
    local.port = BST_PORT;

    if (sock_tcp_listen(&queue, &local, sock_queue, SOCK_QUEUE_LEN, 0) != 0) {
        puts("[Server] Error creating listening queue.");
        return NULL;
    }

    uint16_t lport = 0;
    char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];
    sock_tcp_ep_fmt(&local, ipv6_addr, &lport);

    printf("[Server] Now listening on %s[:%d]\n", ipv6_addr, lport);

    msg_t msg;
    uint8_t q2[32];
    while (1) {
        sock_tcp_t* sock;

        if (msg_try_receive(&msg) == 1) {
            if (msg.content.value == MSG_ACTION_STOP) {
                sock_tcp_stop_listen(&queue);

                msg_t reply;
                reply.content.value = msg.content.value & 0x0;
                msg_reply(&msg, &reply);
                thread_zombify();
            }
        }

        int ret_code = 0;
        if ((ret_code = sock_tcp_accept(&queue, &sock, UINT8_MAX)) != 0) {
            if (ret_code != -ETIMEDOUT) {
                printf("[Server/TCP] Error accepting tcp connection: %d\n", ret_code);
            }

        } else {
            int rres = 0;
            puts("[Server/TCP] Accepted new client.");

            while (rres >= 0) {
                rres = sock_tcp_read(sock, &buf, sizeof(buf), SOCK_NO_TIMEOUT);

                if (rres <= 0) {
                    printf("[Server/TCP] Client disconnected.\n");
                    break;
                } else {
#ifdef DEBUG_LOG
                    printf("[Server/TCP] Received: %d bytes\n", rres);
                    printf("Content: ");
                    for (int i = 0; i < rres; i++)
                        printf("%02x ", buf[i]);
                    printf("\n");
#endif

                    memcpy(&q2, &buf, sizeof(q2));

                    int wres = 0;
                    if ((wres = sock_tcp_write(sock, cparms.q, sizeof(cparms.q))) < 0) {
                        puts("[Server/TCP] Errored on write, finished server loop");
                        break;
                    } else {
                        printf("[Server/TCP] Wrote %d bytes.\n", wres);
                    }
                }
            }

            sock_tcp_disconnect(sock);

            /* Diffie-Hellman exchange */
            printf("[DH] Calculating r ... \n");
            c25519_smult(cparms.r, q2, cparms.e);

#ifdef DEBUG_LOG
            puts("");
            printf("[DH] e: ");
            for (unsigned int i = 0; i < sizeof(cparms.e); i++)
                printf("%02x ", cparms.e[i]);
            printf("\n");

            printf("[DH] q2: ");
            for (unsigned int i = 0; i < sizeof(q2); i++)
                printf("%02x ", q2[i]);
            printf("\n");

            printf("[DH] r: ");
            for (unsigned int i = 0; i < sizeof(cparms.r); i++)
                printf("%02x ", cparms.r[i]);
            printf("\n");
#else
            printf("Done. \n");
#endif

            printf("[SHA3] Calculating hash ... ");
            static unsigned char hash[SHA3_256_DIGEST_LENGTH];
            keccak_state_t state;

            sha3_256_init(&state);
            sha3_update(&state, cparms.r, sizeof(cparms.r));
            sha3_256_final(&state, hash);

            memcpy(AES_KEY_BUF, hash, sizeof(AES_KEY_BUF));

#ifdef DEBUG_LOG
            printf("\n[AES-128] ");
            for (unsigned int i = 0; i < sizeof(AES_KEY_BUF); i++)
                printf("%02x ", AES_KEY_BUF[i]);
            printf("\n");
#endif

            printf(" Done.\n");
        }
    }

    /* Should never be reached */
    return NULL;
}

static int start_server(char* mode) {
    if (strcmp(mode, "plain") != 0 && strcmp(mode, "encrypted") != 0) {
        printf("Error: invalid mode '%s' specified.\n", mode);
        return 1;
    }

    if (server_main_pid != KERNEL_PID_UNDEF && announce_pid != KERNEL_PID_UNDEF) {
        printf("Error: Server is already running.\n");
        return 1;
    }

    if (strcmp(mode, "encrypted") == 0) {
        announce_pid = thread_create(announce_stack, sizeof(announce_stack), THREAD_PRIORITY_MAIN - 1,
                                     THREAD_CREATE_STACKTEST, _announce, NULL, "bst-server-announce");

        server_main_pid = thread_create(server_stack, sizeof(server_stack), THREAD_PRIORITY_MAIN - 2,
                                        THREAD_CREATE_STACKTEST, _server_encrypted_thread, NULL, "bst-server-encrypted");
        return 0;
    }

    if (strcmp(mode, "plain") == 0) {
        printf("Error: Not implemented.\n");
        return 1;
    }

    return 1;
}

static void stop_server(void) {
    if (announce_pid == KERNEL_PID_UNDEF && server_main_pid == KERNEL_PID_UNDEF) {
        puts("Error: Server is not running.");
        return;
    }

    msg_t msg, reply;
    msg.content.value = MSG_ACTION_STOP;

    if (msg_send_receive(&msg, &reply, announce_pid) == 1) {
        if (reply.content.value == 0x0) {
            if (thread_kill_zombie(announce_pid) == 1) {
                puts("Success: announce-thread has been stopped.");
                announce_pid = KERNEL_PID_UNDEF;
            }
        } else {
            printf("Failed to kill zombie: %d\n", reply.content.value);
        }
    }

    if (msg_send_receive(&msg, &reply, server_main_pid) == 1) {
        if (reply.content.value == 0x0) {
            if (thread_kill_zombie(server_main_pid) == 1) {
                puts("Success: Server has been stopped.");
                server_main_pid = KERNEL_PID_UNDEF;
            }
        } else {
            printf("Failed to kill zombiez: %d\n", reply.content.value);
        }
    }
}

int bst_cmd(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s [start|stop]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        if (argc < 3) {
            printf("Usage: %s start [plain|encrypted]\n", argv[0]);
            return 1;
        }

        start_server(argv[2]);

    } else if (strcmp(argv[1], "stop") == 0) {
        stop_server();
    } else {
        puts("Error: invalid command.");
    }

    return 0;
}
