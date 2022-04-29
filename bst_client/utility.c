/**
 * @file utility.c
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#define DAT_START (EEPROM_SIZE - EEPROM_RESERV_CPU_HI - EEPROM_RESERV_BOARD_HI - 1)

#include "include/bst_client.h"

void eeprom_init(void) {
#ifdef DEBUG_LOG
    if (eepreg_check() != 0) {
        printf("[EEPROM] No registry present.\n");

        if (eepreg_reset() != 0) {
            printf("[EEPROM] Failed to write new registry.\n");
        } else {
            printf("[EEPROM] Wrote new registry.\n");
        }
    } else {
        printf("[EEPROM] Registry OK.\n");
    }
#else
    if (eepreg_check() != 0) {
        eepreg_reset();
    }
#endif
}

/**
 * @brief
 *
 * @param ENTRY_NAME
 * @param ENTRY_SIZE
 * @param reg_addr
 * @return int Return 0 if exists, 1 if added, else error
 */
int eeprom_read_entry(char* ENTRY_NAME, size_t ENTRY_SIZE, uint32_t* reg_addr) {
    if (eepreg_read(reg_addr, ENTRY_NAME) != 0) {
        if (eepreg_add(reg_addr, ENTRY_NAME, ENTRY_SIZE) != 0) {
            if (*reg_addr != DAT_START - ENTRY_SIZE) {
                puts("[EEPROM] Error in address length");
                return -1;
            }
        }

        return 1;
    }

    return 0;
}

void gen_aes_key(uint8_t* data, size_t size) {
    // TODO: Improvement: Utilize TRNG featured in Atmega256rfr2 processor.

#ifdef DEBUG_LOG
    printf("[ENCR] Generating key ... \n");
    random_bytes(data, size);

    for (int i = 0; i < 16; i++) {
        printf("0x%.2x ", (uint8_t)data[i]);
    }
    printf("\n");
#else
    random_bytes(data, size);
#endif
}

void print_hw_addr(void) {
#ifdef AVR_RSS2
    eui64_t eui64_addr;
    if (at24mac_get_eui64(0, &eui64_addr) == 0) {
        printf("HWaddr: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n", eui64_addr.uint8[0], eui64_addr.uint8[1], eui64_addr.uint8[2], eui64_addr.uint8[3], eui64_addr.uint8[4], eui64_addr.uint8[5], eui64_addr.uint8[6], eui64_addr.uint8[7]);
    }
#endif
}

void print_ip_addr(void) {
    /* get interfaces and print their addresses */
    gnrc_netif_t* netif = NULL;
    while ((netif = gnrc_netif_iter(netif))) {
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs, sizeof(ipv6_addrs));

        if (res < 0) {
            continue;
        }
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++) {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("inet6 addr: %s\n", ipv6_addr);
        }
    }
}
