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

#include "include/utility.h"

static const uint8_t MSG_ANNOUNCE = 0xD0;
// static const uint8_t MSG_DONE = 0xC8;

static const uint16_t BST_PORT = 8119;
static const uint16_t MULTICAST_PORT = 8561;

static char SERVER_ADDR[IPV6_ADDR_MAX_STR_LEN];

extern struct curve_params cparms;
extern const char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

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

static void _run_client(void) {
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
    printf("[DH] Calculating r ... \n");
    c25519_smult(cparms.r, q2, cparms.e);

#ifdef DEBUG_LOG
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
}

void *bst_client(void *arg) {
    (void)arg;

    _find_server();
    _run_client();

    return 0;
}
