/**
 * @file udps_server.c
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "include/bst_server.h"
#include "include/configs.h"

#define QUEUE_SIZE (2)

static kernel_pid_t udps_pid = KERNEL_PID_UNDEF;
static char udps_stack[THREAD_STACKSIZE_MEDIUM + THREAD_EXTRA_STACKSIZE_PRINTF];
static msg_t udps_message_queue[QUEUE_SIZE];

extern unsigned char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

static void* _udps_server(void* arg) {
    (void)arg;
    msg_init_queue(udps_message_queue, QUEUE_SIZE);

    /* Configure local UDP endpoint */
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;

    local.port = UDPS_PORT;

    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return NULL;
    }

    uint16_t lport = 0;
    char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];
    sock_tcp_ep_fmt(&local, ipv6_addr, &lport);

    cipher_t cipher;
    char* PLAIN_MESSAGE = "Thanks!";
    int msg_len = 8;

    if (cipher_init(&cipher, CIPHER_AES, AES_KEY_BUF, sizeof(AES_KEY_BUF)) != 1) {
        printf("[Server/UDPS] Error initalizing AES.\n");
    }

    printf("[Server/UDPS] Now listening on %s[:%d]\n", ipv6_addr, lport);
    msg_t msg;
    while (1) {
        if (msg_try_receive(&msg) == 1) {
            if (msg.content.value == MSG_ACTION_STOP) {
                sock_udp_close(&sock);

                msg_t reply;
                reply.content.value = msg.content.value & 0x0;
                msg_reply(&msg, &reply);
            }
        }

        sock_udp_ep_t remote;
        ssize_t res;

        uint8_t buf[128];
        uint8_t iv_vector[16];
        uint8_t data[64];
        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT, &remote)) >= 0) {
            printf("[Server/UDPS] Received message (%d bytes) \n", res);

#ifdef DEBUG_LOG
            for (int i = 0; i < res; i++) {
                printf("%02X ", buf[i]);
            }
            printf("\n");
#endif

            memcpy(iv_vector, buf, sizeof(iv_vector));
            memcpy(data, buf + 16, sizeof(data));

            uint8_t decoded_data[sizeof(data)];
            if (cipher_decrypt_cbc(&cipher, iv_vector, data, sizeof(data), decoded_data) < 0) {
                printf("[Server/UDPS] Failed to decrypt data.\n");
            }

            char plain_text[res];
            memcpy(plain_text, decoded_data, sizeof(decoded_data));
            printf("[Server/UDPS] Received message (decrypted): ");
            for (unsigned i = 0; i < strlen(plain_text); ++i) {
                printf("%c", plain_text[i]);
            }
            printf("\n");

            /* Send Response */
            uint8_t PLAIN_TEXT[64];
            memcpy(PLAIN_TEXT, PLAIN_MESSAGE, msg_len);

            /* Pad message */
            for (unsigned i = msg_len; i < sizeof(PLAIN_TEXT); i++) {
                PLAIN_TEXT[i] = '\0';
            }

            random_bytes(iv_vector, sizeof(iv_vector));
            if (cipher_encrypt_cbc(&cipher, iv_vector, PLAIN_TEXT, sizeof(PLAIN_TEXT), data) < 0) {
                puts("[Client/UDPS] Error encrypting data.");
            }

            uint8_t payload[64 + 16];
            memcpy(payload, iv_vector, sizeof(iv_vector));
            memcpy(payload + 16, data, sizeof(data));

            if (sock_udp_send(&sock, payload, sizeof(payload), &remote) < 0) {
                puts("[Server/UDPS] Error sending reply");
            } else {
                puts("[Server/UDPS] Sent response.\n");
            }
        }
    }

    /* Should never be reached */
    return NULL;
}

static int start_server(void) {
    if (udps_pid != KERNEL_PID_UNDEF) {
        printf("Error: Server is already running.\n");
        return 1;
    }

    udps_pid = thread_create(udps_stack, sizeof(udps_stack), THREAD_PRIORITY_MAIN - 3,
                             THREAD_CREATE_STACKTEST, _udps_server, NULL, "udps-server");

    return 0;
}

static int stop_server(void) {
    if (udps_pid == KERNEL_PID_UNDEF) {
        puts("Error: Server is not running.");
        return 0;
    }

    msg_t msg, reply;
    msg.content.value = MSG_ACTION_STOP;

    if (msg_send_receive(&msg, &reply, udps_pid) == 1) {
        if (reply.content.value == 0x0) {
            if (thread_kill_zombie(udps_pid) == 1) {
                puts("Success: udps server has been stopped.");
                udps_pid = KERNEL_PID_UNDEF;
                return 0;
            }
        } else {
            printf("Failed to kill zombie: %d\n", reply.content.value);
            return 1;
        }
    }

    return 0;
}

int udps_cmd(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s [start|stop]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        start_server();
    } else if (strcmp(argv[1], "stop") == 0) {
        stop_server();
    } else {
        puts("Error: invalid command.");
    }

    return 0;
}
