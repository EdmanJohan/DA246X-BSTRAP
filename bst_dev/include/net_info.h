
#ifndef NET_INFO_H
#define NET_INFO_H

#include <stdio.h>
#include <string.h>

#ifdef AVR_RSS2
#include "at24mac.h"
#include "at24mac_params.h"
#endif

#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "net/ipv6/addr.h"

#ifdef __cplusplus
extern "C"
{
#endif

    extern void _print_hw_addr(void);

    extern void _print_ip_addr(void);

#ifdef __cplusplus
}
#endif

#endif
