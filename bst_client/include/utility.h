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

void eeprom_init(void);
uint32_t eeprom_read_entry(char* ENTRY_NAME, size_t ENTRY_SIZE, uint32_t* reg_addr);
void gen_aes_key(uint8_t* data, size_t size);
void print_hw_addr(void);
void print_ip_addr(void);

#ifdef __cplusplus
}
#endif

#endif
