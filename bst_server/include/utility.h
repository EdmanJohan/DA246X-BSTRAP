/**
 * @file utility.h
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UTILITY_H
#define UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

void entropy_init(void);
void gen_keypair(struct curve_params* cparms);
void configure_endpoint(void);

#ifdef __cplusplus
}
#endif

#endif
