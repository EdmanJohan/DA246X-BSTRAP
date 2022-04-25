/**
 * @file net_info.c
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "include/net_info.h"

void _print_hw_addr(void)
{
#ifdef AVR_RSS2
    eui64_t eui64_addr;
    if (at24mac_get_eui64(0, &eui64_addr) == 0)
    {
        printf("HWaddr: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n", eui64_addr.uint8[0], eui64_addr.uint8[1], eui64_addr.uint8[2], eui64_addr.uint8[3], eui64_addr.uint8[4], eui64_addr.uint8[5], eui64_addr.uint8[6], eui64_addr.uint8[7]);
    }
#endif
}

void _print_ip_addr(void)
{
    /* get interfaces and print their addresses */
    gnrc_netif_t *netif = NULL;
    while ((netif = gnrc_netif_iter(netif)))
    {
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs,
                                  sizeof(ipv6_addrs));

        if (res < 0)
        {
            continue;
        }
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++)
        {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("inet6 addr: %s\n", ipv6_addr);
        }
    }
}
