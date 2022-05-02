/**
 * @file bst_client.c
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "include/bst_client.h"

#include "crypto/ciphers.h"
#include "crypto/modes/cbc.h"
#include "include/utility.h"

static const uint8_t MSG_ANNOUNCE = 0xD0;

static const uint16_t BST_PORT = 8119;
static const uint16_t MULTICAST_PORT = 8561;
static const uint16_t DATA_PORT = 8889;

static char SERVER_ADDR[IPV6_ADDR_MAX_STR_LEN];

extern struct curve_params cparms;
extern unsigned char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

static int _find_server(void) {
    /* Await broadcast from server. */
    uint8_t buf[128];
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    local.port = MULTICAST_PORT;
    sock_udp_t sock;

    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("[Client/UDP] Error creating UDP sock");
        return 1;
    }

    while (1) {
        sock_udp_ep_t remote;
        ssize_t res;
        char addrstr[IPV6_ADDR_MAX_STR_LEN];
        uint16_t rport;

        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT, &remote)) >= 0) {
            sock_udp_ep_fmt(&remote, addrstr, &rport);

#ifdef DEBUG_LOG
            printf("[Client/UDP] Received a message from: %s[:%u]\n\t     Message: ", addrstr, rport);
            for (int i = 0; i < res; i++) {
                printf("%c", buf[i]);
            }
            printf("\n");
#endif

            if (strncmp((char *)buf, (char *)&MSG_ANNOUNCE, res) == 0) {
                ipv6_addr_to_str(SERVER_ADDR, (ipv6_addr_t *)&remote.addr.ipv6, sizeof(SERVER_ADDR));
                sock_udp_close(&sock);
                break;
            }
        }
    }

    return 0;
}

static void _exchange_keys(void) {
    uint8_t buf[128];
    sock_tcp_ep_t remote = SOCK_IPV6_EP_ANY;
    sock_tcp_t sock;

    remote.port = BST_PORT;
    ipv6_addr_from_str((ipv6_addr_t *)&remote.addr, SERVER_ADDR);
    printf("[Client/TCP] Trying to connect to: %s[:%d]\n", SERVER_ADDR, BST_PORT);

    uint8_t q2[32];
    uint8_t conn_retry = 0;
    while (conn_retry == 0) {
        if (sock_tcp_connect(&sock, &remote, 0, 0) != 0) {
            puts("[Client/TCP] Error connecting sock");
        } else {
            puts("[Client/TCP] Connected.");
            conn_retry = 1;
        }
    }

    int wrres = 0;
    if (sock_tcp_write(&sock, cparms.q, sizeof(cparms.q)) < 0) {
        puts("[Client/TCP] Errored on write");
    } else {
        printf("[Client/TCP] Wrote %d bytes.\n", wrres);
        int rres = 0;
        if ((rres = sock_tcp_read(&sock, &buf, sizeof(buf), SOCK_NO_TIMEOUT)) <= 0) {
            puts("[Client/TCP] Disconnected");
        }

#ifdef DEBUG_LOG
        printf("[Client/TCP] Received: %d bytes\n", rres);
        printf("Content: ");
        for (int i = 0; i < rres; i++)
            printf("%02x ", buf[i]);
        printf("\n");
#endif

        memcpy(&q2, &buf, sizeof(q2));
    }

    printf("[Client/TCP] Disconnecting from session.\n");
    sock_tcp_disconnect(&sock);

    /* Diffie-Hellman exchange */
    printf("[DH] Calculating r ... ");
    uint32_t start = xtimer_now_usec();
    c25519_smult(cparms.r, q2, cparms.e);
    uint32_t end = xtimer_now_usec();

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
#endif
    printf("Done. Took %u us\n", (end - start));
}

void _hash_secret_key(void) {
    printf("[SHA3] Calculating hash ... ");

    static unsigned char hash[SHA3_256_DIGEST_LENGTH];
    keccak_state_t state;

    uint32_t start = xtimer_now_usec();
    sha3_256_init(&state);
    sha3_update(&state, cparms.r, sizeof(cparms.r));
    sha3_256_final(&state, hash);
    uint32_t end = xtimer_now_usec();

    memcpy(AES_KEY_BUF, hash, sizeof(AES_KEY_BUF));

#ifdef DEBUG_LOG
    printf("\n[AES-128] ");
    for (unsigned int i = 0; i < sizeof(AES_KEY_BUF); i++)
        printf("%02x ", AES_KEY_BUF[i]);
    printf("\n");
#endif

    printf("Done. Took %u us\n", (end - start));
}

int _send_data(void) {
    cipher_t cipher;
    char *PLAIN_MESSAGE = "Wow very encrypt!";
    int msg_len = 18;

    if (cipher_init(&cipher, CIPHER_AES, AES_KEY_BUF, sizeof(AES_KEY_BUF)) != 1) {
        printf("[Client/UDPS] Error initalizing AES.\n");
    }

    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = 0xabcd;

    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }

    uint8_t buf[128];
    uint8_t iv_vector[16];
    uint8_t data[64];
    while (1) {
        sock_udp_ep_t remote = {.family = AF_INET6};
        ssize_t res;

        remote.port = DATA_PORT;
        ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6, IPV6_ADDR_MCAST_SCP_LINK_LOCAL);

        uint8_t PLAIN_TEXT[64];
        memcpy(PLAIN_TEXT, PLAIN_MESSAGE, msg_len);
        for (unsigned i = msg_len; i < sizeof(PLAIN_TEXT); i++) {
            PLAIN_TEXT[i] = '\0';
        }

        random_bytes(iv_vector, sizeof(iv_vector));
        if (cipher_encrypt_cbc(&cipher, iv_vector, PLAIN_TEXT, sizeof(PLAIN_TEXT), data) < 0) {
            printf("[Client/UDPS] Error encrypting data. \n");
        }

        uint8_t payload[64 + 16];
        memcpy(payload, iv_vector, sizeof(iv_vector));
        memcpy(payload + 16, data, sizeof(data));

        if (sock_udp_send(&sock, payload, sizeof(payload), &remote) < 0) {
            puts("[Client/UDPS] Error sending message");
            sock_udp_close(&sock);
            return 1;
        } else {
            puts("[Client/UDPS] Sent message.");
        }

        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), 1 * US_PER_SEC, NULL)) < 0) {
            if (res != -ETIMEDOUT) {
                puts("[Client/UDPS] Error receiving message");
            }
        } else {
            printf("[Client/UDPS] Received message (%d bytes). \n", res);

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
            puts("\n");
        }

        xtimer_sleep(10);
    }

    return 0;
}

void *bst_client(void *arg) {
    (void)arg;

    _find_server();
    _exchange_keys();
    _hash_secret_key();
    _send_data();

    return 0;
}
