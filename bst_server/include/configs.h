/**
 * @file configs.h
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CONFIGS_H
#define CONFIGS_H

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t MSG_ACTION_STOP;
extern const uint8_t MSG_ANNOUNCE;

extern const uint16_t BST_PORT;
extern const uint16_t MULTICAST_PORT;
extern const uint16_t UDPS_PORT;

extern const char* GLOBAL_ADDR;

#ifdef __cplusplus
}
#endif

#endif
