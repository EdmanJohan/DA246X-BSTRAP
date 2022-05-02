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
#include "random.h"
#include "xtimer.h"
#include "ztimer.h"

uint8_t e1[C25519_EXPONENT_SIZE];
uint8_t e2[C25519_EXPONENT_SIZE];
uint8_t q1[F25519_SIZE];
uint8_t q2[F25519_SIZE];
uint8_t r1[F25519_SIZE];
uint8_t r2[F25519_SIZE];

int main(void) {
    uint8_t runs = 10;

    do {
        /* Generate key material */
        uint32_t _benchmark_time = ztimer_now(ZTIMER_USEC);
        for (unsigned long i = 0; i < runs; i++) {
            for (unsigned i = 0; i < sizeof(e1); i++) {
                e1[i] = random();
            }
        }
        _benchmark_time = (ztimer_now(ZTIMER_USEC) - _benchmark_time);
        benchmark_print_time(_benchmark_time, runs, "random");

        /* Create private key */
        _benchmark_time = ztimer_now(ZTIMER_USEC);
        for (unsigned long i = 0; i < runs; i++) {
            c25519_prepare(e1);
        }
        _benchmark_time = (ztimer_now(ZTIMER_USEC) - _benchmark_time);
        benchmark_print_time(_benchmark_time, runs, "c5519_prepare");

        /* Create public key */
        _benchmark_time = ztimer_now(ZTIMER_USEC);
        for (unsigned long i = 0; i < runs; i++) {
            c25519_smult(q1, c25519_base_x, e1);
        }
        _benchmark_time = (ztimer_now(ZTIMER_USEC) - _benchmark_time);
        benchmark_print_time(_benchmark_time, runs, "c25519_smult pubkey");

        /* Other half */
        for (unsigned i = 0; i < sizeof(e2); i++) {
            e2[i] = random();
        }

        c25519_prepare(e2);
        c25519_smult(q2, c25519_base_x, e2);

        /* Key exchange */
        _benchmark_time = ztimer_now(ZTIMER_USEC);
        for (unsigned long i = 0; i < runs; i++) {
            c25519_smult(r1, q2, e1);
        }
        _benchmark_time = (ztimer_now(ZTIMER_USEC) - _benchmark_time);
        benchmark_print_time(_benchmark_time, runs, "c25519_smult DH");

        puts("Done running all.");
        /* TOTAL */
        _benchmark_time = ztimer_now(ZTIMER_USEC);
        for (unsigned long i = 0; i < runs; i++) {
            for (unsigned i = 0; i < sizeof(e1); i++) {
                e1[i] = random();
            }
            c25519_prepare(e1);
            c25519_smult(q1, c25519_base_x, e1);
            c25519_smult(r1, q2, e1);
        }
        _benchmark_time = (ztimer_now(ZTIMER_USEC) - _benchmark_time);
        benchmark_print_time(_benchmark_time, runs, "total run DH exchange");

    } while (0);

    return 0;
}
