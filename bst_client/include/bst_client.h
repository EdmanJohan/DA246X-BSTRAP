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

#include "net/af.h"
#include "net/ipv6/addr.h"
#include "net/protnum.h"
#include "net/sock/udp.h"
#include "xtimer.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int bst_client(void);

#ifdef __cplusplus
}
#endif

#endif
