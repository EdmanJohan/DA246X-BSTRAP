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

#include "include/bst_client.h"
#include "include/utility.h"

#define MAIN_QUEUE_SIZE (8)

#define IP_ADDR_MOTHER_SIZE IPV6_ADDR_MAX_STR_LEN  // (1.) EEPROM Addr of server
#define SYM_KEY_SIZE (16U)                         // (2.) EEPROM AES-128

#define ENT1_NAME "aes"
#define ENT1_SIZE SYM_KEY_SIZE

static char AES_KEY_BUF[SYM_KEY_SIZE];
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
char line_buf[SHELL_DEFAULT_BUFSIZE];

static char client_stack[THREAD_STACKSIZE_MAIN];

void encr_init(void) {
    uint32_t reg_addr;
    if (eeprom_read_entry(ENT1_NAME, ENT1_SIZE, &reg_addr) == 1) {
        gen_aes_key((uint8_t*)AES_KEY_BUF, SYM_KEY_SIZE);
        eeprom_write(reg_addr, (uint8_t*)AES_KEY_BUF, sizeof(AES_KEY_BUF));
        puts("[EEPROM] Wrote AES-KEY to EEPROM.\n");
    } else {
        eeprom_read(reg_addr, (uint8_t*)AES_KEY_BUF, sizeof(AES_KEY_BUF));
#ifdef DEBUG_LOG
        printf("Key: ");
        for (int i = 0; i < 16; i++) {
            printf("0x%.2x ", (uint8_t)AES_KEY_BUF[i]);
        }
        printf("\n");
#endif
        puts("[EEPROM] Read AES-KEY from EEPROM.\n");
    }
}

int main(void) {
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("DA246X Bootstrapper | CLIENT");

    print_hw_addr();  // Print HW Addr
    print_ip_addr();  // Print IP Addr

    eeprom_init();  // Init EEPROM
    encr_init();    // Initalize/Read AES key to buffer.

    // TODO: If not, then generate symmetric key and save

    // Check if server wants key transfer, otherwise ok to communicate
    thread_create(client_stack, sizeof(client_stack), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, bst_client, NULL, "bst-client");

    // Establish secure channel and communicate

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run_forever(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
