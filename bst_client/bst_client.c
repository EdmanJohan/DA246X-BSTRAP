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

static uint16_t BST_PORT = 1119;
// static uint16_t SBST_PORT = 9119;

int bst_client(void)
{
    sock_udp_ep_t remote = {.family = AF_INET6};
    remote.port = BST_PORT;
    ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6,
                                      IPV6_ADDR_MCAST_SCP_LINK_LOCAL);
    while (1)
    {
        sock_udp_send(NULL, "Hello!", sizeof("Hello!"), &remote);
        puts("Sent message.");
        xtimer_sleep(1);
    }
}
