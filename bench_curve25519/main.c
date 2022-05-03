/**
 * @file main.c
 * @author Johan Edman (jedma@kth.se)
 * @brief Benchmark Curve25519 computations
 * @version 0.1
 * @date 2022-05-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "benchmark.h"
#include "c25519.h"
#include "hashes/sha3.h"
#include "random.h"
#include "xtimer.h"
#include "ztimer.h"

uint8_t e1[C25519_EXPONENT_SIZE];
uint8_t e2[C25519_EXPONENT_SIZE];
uint8_t q1[F25519_SIZE];
uint8_t q2[F25519_SIZE];
uint8_t r1[F25519_SIZE];

uint8_t runs = 10;

void gen_key_material(void) {
    /* Generate key material */
    uint32_t _benchmark_times[runs];
    for (unsigned long i = 0; i < runs; i++) {
        _benchmark_times[i] = ztimer_now(ZTIMER_USEC);

        for (unsigned j = 0; j < sizeof(e1); j++) {
            e1[j] = random();
        }

        _benchmark_times[i] = (ztimer_now(ZTIMER_USEC) - _benchmark_times[i]);
    }

    uint32_t _benchmark_time = 0;
    for (unsigned i = 0; i < runs; i++) {
        _benchmark_time += _benchmark_times[i];
    }
    benchmark_print_time(_benchmark_time, runs, "random");

    printf("Individual times: \n");
    for (unsigned i = 0; i < runs; i++) {
        printf(" %9" PRIu32 ", ", _benchmark_times[i]);
    }
    printf("\n\n");
}

void gen_private_key(void) {
    /* Create private key */
    uint32_t _benchmark_times[runs];
    for (unsigned long i = 0; i < runs; i++) {
        _benchmark_times[i] = ztimer_now(ZTIMER_USEC);

        c25519_prepare(e1);

        _benchmark_times[i] = (ztimer_now(ZTIMER_USEC) - _benchmark_times[i]);
    }

    uint32_t _benchmark_time = 0;
    for (unsigned i = 0; i < runs; i++) {
        _benchmark_time += _benchmark_times[i];
    }
    benchmark_print_time(_benchmark_time, runs, "c5519_prepare");

    printf("Individual times: \n");
    for (unsigned i = 0; i < runs; i++) {
        printf(" %9" PRIu32 ", ", _benchmark_times[i]);
    }
    printf("\n\n");
}

void gen_public_key(void) {
    /* Create public key */
    uint32_t _benchmark_times[runs];
    for (unsigned long i = 0; i < runs; i++) {
        _benchmark_times[i] = ztimer_now(ZTIMER_USEC);

        c25519_smult(q1, c25519_base_x, e1);

        _benchmark_times[i] = (ztimer_now(ZTIMER_USEC) - _benchmark_times[i]);
    }

    uint32_t _benchmark_time = 0;
    for (unsigned i = 0; i < runs; i++) {
        _benchmark_time += _benchmark_times[i];
    }
    benchmark_print_time(_benchmark_time, runs, "c25519_smult pubkey");

    printf("Individual times: \n");
    for (unsigned i = 0; i < runs; i++) {
        printf(" %9" PRIu32 ", ", _benchmark_times[i]);
    }
    printf("\n\n");
}

void key_exchange(void) {
    /* Key exchange */
    uint32_t _benchmark_times[runs];
    for (unsigned long i = 0; i < runs; i++) {
        _benchmark_times[i] = ztimer_now(ZTIMER_USEC);

        c25519_smult(r1, q2, e1);

        _benchmark_times[i] = (ztimer_now(ZTIMER_USEC) - _benchmark_times[i]);
    }

    uint32_t _benchmark_time = 0;
    for (unsigned i = 0; i < runs; i++) {
        _benchmark_time += _benchmark_times[i];
    }
    benchmark_print_time(_benchmark_time, runs, "c25519_smult DH");

    printf("Individual times: \n");
    for (unsigned i = 0; i < runs; i++) {
        printf(" %9" PRIu32 ", ", _benchmark_times[i]);
    }
    printf("\n\n");
}

void hash_secret(void) {
    static unsigned char hash[SHA3_256_DIGEST_LENGTH];
    keccak_state_t state;

    uint32_t _benchmark_times[runs];
    for (unsigned long i = 0; i < runs; i++) {
        _benchmark_times[i] = ztimer_now(ZTIMER_USEC);

        sha3_256_init(&state);
        sha3_update(&state, r1, sizeof(r1));
        sha3_256_final(&state, hash);

        _benchmark_times[i] = (ztimer_now(ZTIMER_USEC) - _benchmark_times[i]);
    }

    uint32_t _benchmark_time = 0;
    for (unsigned i = 0; i < runs; i++) {
        _benchmark_time += _benchmark_times[i];
    }
    benchmark_print_time(_benchmark_time, runs, "sha3-256 hash");

    printf("Individual times: \n");
    for (unsigned i = 0; i < runs; i++) {
        printf(" %9" PRIu32 ", ", _benchmark_times[i]);
    }
    printf("\n\n");
}

void full_procedure(void) {
    static unsigned char hash[SHA3_256_DIGEST_LENGTH];
    keccak_state_t state;

    uint32_t _benchmark_times[runs];
    for (unsigned long i = 0; i < runs; i++) {
        _benchmark_times[i] = ztimer_now(ZTIMER_USEC);
        for (unsigned i = 0; i < sizeof(e1); i++) {
            e1[i] = random();
        }
        c25519_prepare(e1);
        c25519_smult(q1, c25519_base_x, e1);
        c25519_smult(r1, q2, e1);

        sha3_256_init(&state);
        sha3_update(&state, r1, sizeof(r1));
        sha3_256_final(&state, hash);

        _benchmark_times[i] = (ztimer_now(ZTIMER_USEC) - _benchmark_times[i]);
    }

    uint32_t _benchmark_time = 0;
    for (unsigned i = 0; i < runs; i++) {
        _benchmark_time += _benchmark_times[i];
    }
    benchmark_print_time(_benchmark_time, runs, "total run DH exchange");

    printf("Individual times: \n");
    for (unsigned i = 0; i < runs; i++) {
        printf(" %9" PRIu32 ", ", _benchmark_times[i]);
    }
    printf("\n\n");
}

int main(void) {
    do {
        gen_key_material();
        gen_private_key();
        gen_public_key();

        /* Other half */
        for (unsigned i = 0; i < sizeof(e2); i++) {
            e2[i] = random();
        }

        c25519_prepare(e2);
        c25519_smult(q2, c25519_base_x, e2);
        /* *** */

        key_exchange();
        hash_secret();

        puts("Done running all.");

        /* TOTAL */
        full_procedure();

    } while (0);

    return 0;
}
