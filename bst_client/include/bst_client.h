/**
 * @file bst_client.h
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BST_CLIENT_H
#define BST_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "eepreg.h"
#include "msg.h"
#include "net/af.h"
#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "net/ipv6/addr.h"
#include "net/protnum.h"
#include "net/sock.h"
#include "net/sock/tcp.h"
#include "net/sock/udp.h"
#include "net/sock/util.h"
#include "periph/eeprom.h"
#include "random.h"
#include "shell.h"
#include "thread.h"

#ifdef AVR_RSS2
#include "at24mac.h"
#include "at24mac_params.h"
#endif

extern void *bst_client(void *arg);

#ifdef __cplusplus
}
#endif

#endif
