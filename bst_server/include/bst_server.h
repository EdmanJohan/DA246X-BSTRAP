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

#define EXPONENT_SIZE (32)
#define SYMMETRIC_KEY_BYTES (16U)

#include <stdio.h>

#include "blake2.h"
#include "c25519.h"
#include "errno.h"
#include "msg.h"
#include "net/sock/tcp.h"
#include "net/sock/udp.h"
#include "net/sock/util.h"
#include "random.h"
#include "shell.h"
#include "xtimer.h"

#ifdef AVR_RSS2
#include "at24mac.h"
#include "at24mac_params.h"
#include "entropy_source.h"
#include "entropy_source/adc_noise.h"
#include "periph/adc.h"
#endif

#ifdef DEBUG_LOG
#include "od.h"
#endif

extern void *BST_SERVER(void *arg);

struct curve_params {
    uint8_t q[EXPONENT_SIZE];
    uint8_t e[EXPONENT_SIZE];
    uint8_t r[EXPONENT_SIZE];
};

#ifdef __cplusplus
}
#endif

#endif
