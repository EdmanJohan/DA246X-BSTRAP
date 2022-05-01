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

struct curve_params cparms;
unsigned char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
static char client_stack[THREAD_STACKSIZE_MAIN];

void print_motd(void) {
#ifdef DEBUG_LOG
    puts("DA246X Bootstrapper | CLIENT | DEBUG");
    print_hw_addr();  // Print HW Addr
    print_ip_addr();  // Print IP Addr
#else
    puts("DA246X Bootstrapper | CLIENT");
#endif
}

int main(void) {
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    print_motd();

    eeprom_init();         // Initialize EEPROM
    entropy_init();        // Initialize entropy source
    gen_keypair(&cparms);  // Initialize PubPriv keys

    // encr_init();  // Initalize/Read AES key to buffer.

    // Check if server wants key transfer, otherwise ok to communicate
    thread_create(client_stack, sizeof(client_stack), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, bst_client, NULL, "bst-client");

#ifdef DEBUG_LOG
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run_forever(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
#endif
    return 0;
}
