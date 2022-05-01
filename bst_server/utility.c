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

#include "include/bst_server.h"

static uint8_t CONFIGURED = 0x0u;
static const char* GLOBAL_ADDR = "2001:db8::1";

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

void configure_endpoint(void) {
    if (CONFIGURED == 0x1) {
        return;
    }

    gnrc_netif_t* netif = NULL;

    if (gnrc_netif_numof() == 1) {
        ipv6_addr_t glob_addr;
        ipv6_addr_from_str(&glob_addr, GLOBAL_ADDR);
        netif = gnrc_netif_iter(netif);

        gnrc_netif_ipv6_addr_add(netif, &glob_addr, 64, 0);
    }

    netif = NULL;
    uint8_t devNum = 0;
    while ((netif = gnrc_netif_iter(netif))) {
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs, sizeof(ipv6_addrs));

        if (res < 0) {
            continue;
        }

        printf("[Server] Addresses on dev%d:\n", devNum);
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++) {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("\t[%u] %s\n", i, ipv6_addr);
        }
        devNum++;
    }

    CONFIGURED = 0x1;
}
