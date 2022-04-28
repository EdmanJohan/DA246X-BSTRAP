/**
 * @file main.c
 * @author Johan Edman (jedma@kth.se)
 * @brief DA246X Bootstrapper client
 * @version 0.1
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>

#include "eepreg.h"
#include "include/bst_client.h"
#include "include/net_info.h"
#include "msg.h"
#include "periph/eeprom.h"
#include "shell.h"
#include "thread.h"

#define MAIN_QUEUE_SIZE (8)
#define DAT_START (EEPROM_SIZE - EEPROM_RESERV_CPU_HI - EEPROM_RESERV_BOARD_HI - 1)

// EEPROM
// 1. IP address of mother node
// 2. Symmetric Key AES-128
#define IP_ADDR_MOTHER_SIZE IPV6_ADDR_MAX_STR_LEN

#define ENTRY2_NAME "SKEY"
#define ENTRY2_SIZE (12U)
#define DATA "i am teapot"

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
char line_buf[SHELL_DEFAULT_BUFSIZE];

static char client_stack[THREAD_STACKSIZE_MAIN];

void initalize_eep(void) {
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
}

int main(void) {
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("DA246X Bootstrapper | CLIENT");

    print_hw_addr();
    print_ip_addr();

    initalize_eep();
    // TODO: Generate symmetric key

    thread_create(client_stack, sizeof(client_stack), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, bst_client, NULL, "bst-client");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run_forever(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
