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

#define ENT1_NAME "aes"
#define ENT1_SIZE SYMMETRIC_KEY_BYTES
#define DAT_START (EEPROM_SIZE - EEPROM_RESERV_CPU_HI - EEPROM_RESERV_BOARD_HI - 1)

#include "include/bst_client.h"

extern unsigned char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

void entropy_init(void) {
    // TODO: Improvement: Utilize TRNG as SRAND, featured in Atmega256rfr2 processor.
#ifdef AVR_RSS2
    printf("[ENTROPY] Inititalizing w. seed from ADC ... ");
    uint8_t buf[sizeof(uint32_t)];
    uint32_t seed;

    /* Initialize ADC noise source */
    entropy_source_adc_init();
    entropy_source_adc_get(buf, sizeof(uint32_t));
    memcpy(&seed, &buf[0], sizeof(seed));
    random_init(seed);
    printf("Done. \n");
#else
    uint32_t seed = 42;
#endif

#ifdef DEBUG_LOG
    printf("[ENTROPY] Seed: %u\n", seed);
#endif
    random_init(seed);
}

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
    random_bytes(data, size);

#ifdef DEBUG_LOG
    printf("[ENCR] Generated key: \n");

    for (int i = 0; i < 16; i++) {
        printf("0x%.2x ", (uint8_t)data[i]);
    }
    printf("\n");
#endif
}

void encr_init(void) {
    uint32_t reg_addr;

    if (eeprom_read_entry(ENT1_NAME, ENT1_SIZE, &reg_addr) == 1) {
        gen_aes_key((uint8_t*)AES_KEY_BUF, SYMMETRIC_KEY_BYTES);
        eeprom_write(reg_addr, (uint8_t*)AES_KEY_BUF, sizeof(AES_KEY_BUF));
        puts("[EEPROM] Wrote AES-KEY to EEPROM.\n");
    } else {
        eeprom_read(reg_addr, (uint8_t*)AES_KEY_BUF, sizeof(AES_KEY_BUF));

#ifdef DEBUG_LOG
        printf("[EEPROM] Key: ");
        for (int i = 0; i < 16; i++) {
            printf("0x%.2x ", (uint8_t)AES_KEY_BUF[i]);
        }
        printf("\n");
#endif

        puts("[EEPROM] Read AES-KEY from EEPROM.\n");
    }
}

/**
 * @brief Generate CD25519 PubPriv Keypair
 *
 * @param cparms Struct for params
 */
void gen_keypair(struct curve_params* cparms) {
    printf("[DH-GEN] Generating CD25519 PubPriv keys ... ");
    uint32_t start = xtimer_now_usec();

    /* Generate private keys */
    random_bytes(cparms->e, sizeof(cparms->e));

    /* Create private keys */
    c25519_prepare(cparms->e);

    /* Create public keys */
    c25519_smult(cparms->q, c25519_base_x, cparms->e);

    uint32_t end = xtimer_now_usec();

    printf("Done. Took %u us\n", (end - start));

#if DEBUG_LOG
    printf("\n[DH-GEN] Param e: \n");
    od_hex_dump(cparms->e, sizeof(cparms->e), 0);

    printf("\n[DH-GEN] Param q: \n");
    od_hex_dump(cparms->q, sizeof(cparms->q), 0);
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
