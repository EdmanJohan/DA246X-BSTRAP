/**
 * @file main.c
 * @author Johan Edman (jedma@kth.se)
 * @brief Sample data from ADC for entropy evaluation
 * @version 0.1
 * @date 2022-05-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "entropy_source.h"
#include "entropy_source/adc_noise.h"
#include "entropy_source/zero_entropy.h"
#include "fmt.h"
#include "xtimer.h"

// ADC 10-bit Resolution

int main(void) {
    int ret;
    uint8_t buf1;

    /* Initialize ADC noise source */
    entropy_source_adc_init();

    while (1) {
        /*Request single bytes*/
        ret = entropy_source_adc_get(&buf1, 1);
        if (ret >= 0) {
            printf("%02x", buf1);
        }
    }

    return 0;
}
