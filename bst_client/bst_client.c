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

#include "net/af.h"
#include "net/ipv6/addr.h"
#include "net/protnum.h"
#include "net/sock.h"
#include "net/sock/tcp.h"
#include "net/sock/udp.h"
#include "net/sock/util.h"

static uint16_t BST_PORT = 8119;
static uint16_t MULTICAST_PORT = 8561;
uint8_t buf[128];

static char SERVER_ADDR[IPV6_ADDR_MAX_STR_LEN];

static int _find_server(void) {
    /* Await broadcast from server. */
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    local.port = MULTICAST_PORT;
    sock_udp_t sock;

    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }

    while (1) {
        sock_udp_ep_t remote;
        ssize_t res;
        char addrstr[IPV6_ADDR_MAX_STR_LEN];
        uint16_t rport;

        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT, &remote)) >= 0) {
            sock_udp_ep_fmt(&remote, addrstr, &rport);

            //#ifdef DEBUG_LOG
            printf("[Client/UDP] Received a message from: %s[:%u]\n\t     Message: ", addrstr, rport);
            for (int i = 0; i < res; i++) {
                printf("%c", buf[i]);
            }
            puts("");
            //#endif

            if (strncmp((char *)buf, "ANNOUNCE", res) == 0) {
                ipv6_addr_to_str(SERVER_ADDR, (ipv6_addr_t *)&remote.addr.ipv6, sizeof(SERVER_ADDR));
                sock_udp_close(&sock);
                // printf("[Client/UDP: Server is %s\n", SERVER_ADDR);
                // puts("[Client/UDP] Exiting thread.");
                break;
            }
        }
    }

    return 0;
}

static int _run_client(void) {
    int res;
    sock_tcp_ep_t remote = SOCK_IPV6_EP_ANY;
    sock_tcp_t sock;

    int retry = 0;
    remote.port = BST_PORT;
    ipv6_addr_from_str((ipv6_addr_t *)&remote.addr, SERVER_ADDR);
    // ipv6_addr_from_str((ipv6_addr_t *)&remote.addr, "fe80::fec2:3d00:1:856e");
    printf("Trying to connect to: %s[:%d]\n", SERVER_ADDR, BST_PORT);
    while (retry == 0) {
        if (sock_tcp_connect(&sock, &remote, 0, 0) < 0) {
            puts("Error connecting sock");
        } else {
            retry = 1;
        }
    }

    puts("Sending \"Hello!\"");
    if ((res = sock_tcp_write(&sock, "Hello!", sizeof("Hello!"))) < 0) {
        puts("Errored on write");
    } else {
        if ((res = sock_tcp_read(&sock, &buf, sizeof(buf),
                                 SOCK_NO_TIMEOUT)) <= 0) {
            puts("Disconnected");
        }
        printf("Read: \"");
        for (int i = 0; i < res; i++) {
            printf("%c", buf[i]);
        }
        puts("\"");
    }
    sock_tcp_disconnect(&sock);
    return res;
}

void *bst_client(void *arg) {
    (void)arg;
    // Start DISCOVER
    _find_server();
    _run_client();

    return 0;
}
