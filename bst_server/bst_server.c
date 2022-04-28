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

#include <stdio.h>

#include "errno.h"
#include "msg.h"
#include "net/sock/tcp.h"
#include "net/sock/udp.h"
#include "net/sock/util.h"
#include "xtimer.h"

#define SOCK_QUEUE_LEN (1U)
#define QUEUE_SIZE (2)

static uint8_t CONFIGURED = 0x0u;
static const uint8_t MSG_ACTION_STOP = 0x1u;
static const uint8_t MSG_ANNOUNCE = 0xD0;

static const uint16_t BST_PORT = 8119;
// static uint16_t SBST_PORT = 8819;
static const uint16_t MULTICAST_PORT = 8561;
static const char* GLOBAL_ADDR = "2001:db8::1";

static kernel_pid_t announce_pid = KERNEL_PID_UNDEF;
static char announce_stack[THREAD_STACKSIZE_DEFAULT];
static msg_t announce_msg_queue[QUEUE_SIZE];

static kernel_pid_t server_main_pid = KERNEL_PID_UNDEF;
static char server_stack[THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF];
static msg_t server_msg_queue[QUEUE_SIZE];

static sock_tcp_t sock_queue[SOCK_QUEUE_LEN];

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

static void configure_endpoint(void) {
    if (CONFIGURED == 0x1) {
        return;
    }

    gnrc_netif_t* netif = NULL;

    if (gnrc_netif_numof() == 1) {
        ipv6_addr_t glob_addr;
        ipv6_addr_from_str(&glob_addr, GLOBAL_ADDR);
        netif = gnrc_netif_iter(netif);

        gnrc_netif_ipv6_addr_add(netif, &glob_addr, 64, 0);
    }

    netif = NULL;
    uint8_t devNum = 0;
    while ((netif = gnrc_netif_iter(netif))) {
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs, sizeof(ipv6_addrs));

        if (res < 0) {
            continue;
        }

        printf("[Server] Addresses on dev%d:\n", devNum);
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++) {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("\t[%u] %s\n", i, ipv6_addr);
        }
        devNum++;
    }

    CONFIGURED = 0x1;
}

static void* _server_thread(void* arg) {
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
                printf("Error accepting tcp connection: %d\n", ret_code);
            }

        } else {
            int read_res = 0;
            puts("[Server] Accepted new client.");

            while (read_res >= 0) {
                read_res = sock_tcp_read(sock, &buf, sizeof(buf), SOCK_NO_TIMEOUT);

                if (read_res <= 0) {
                    printf("[Server] Client disconnected.\n");
                    break;
                } else {
                    int write_res;

                    printf("Read: \"");
                    for (int i = 0; i < read_res; i++) {
                        printf("%c", buf[i]);
                    }

                    puts("\"");
                    if ((write_res = sock_tcp_write(sock, &buf, read_res)) < 0) {
                        puts("Errored on write, finished server loop");
                        break;
                    }
                }
            }

            sock_tcp_disconnect(sock);
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

    configure_endpoint();
    announce_pid = thread_create(announce_stack, sizeof(announce_stack), THREAD_PRIORITY_MAIN - 1,
                                 THREAD_CREATE_STACKTEST, _announce, NULL, "bst-server-announce");

    server_main_pid = thread_create(server_stack, sizeof(server_stack), THREAD_PRIORITY_MAIN - 2,
                                    THREAD_CREATE_STACKTEST, _server_thread, NULL, "bst-server");

    return 0;
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

        if (strcmp(argv[1], "start") == 0) {
            start_server(argv[2]);
        }
    } else if (strcmp(argv[1], "stop") == 0) {
        stop_server();
    } else {
        puts("Error: invalid command.");
    }

    return 0;
}
