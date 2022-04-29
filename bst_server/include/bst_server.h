/**
 * @file bst_server.h
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BST_SERVER_H
#define BST_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "errno.h"
#include "msg.h"
#include "net/sock/tcp.h"
#include "net/sock/udp.h"
#include "net/sock/util.h"
#include "xtimer.h"

#ifdef AVR_RSS2
#include "at24mac.h"
#include "at24mac_params.h"
#endif

extern void *BST_SERVER(void *arg);

#ifdef __cplusplus
}
#endif

#endif
