/**
 * @file main.c
 * @author Johan Edman (jedma@kth.se)
 * @brief DA246X Bootstrapper client
 * @version 0.1
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include "include/net_info.h"

#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "xtimer.h"

static uint16_t BST_PORT = 1119;

int main(void)
{
    puts("DA246X Bootstrapper | CLIENT");

    _print_hw_addr();
    _print_ip_addr();

    sock_udp_ep_t remote = {.family = AF_INET6};
    remote.port = BST_PORT;
    ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6,
                                      IPV6_ADDR_MCAST_SCP_LINK_LOCAL);
    while (1)
    {
        sock_udp_send(NULL, "Hello!", sizeof("Hello!"), &remote);
        xtimer_sleep(5);
    }

    return 0;
}
