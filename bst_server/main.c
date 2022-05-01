/**
 * @file main.c
 * @author Johan Edman (jedma@kth.se)
 * @brief DA246X Bootstrapper server
 * @version 0.1
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "include/bst_server.h"
#include "include/utility.h"

#define MAIN_QUEUE_SIZE (8)

struct curve_params cparms;
const char AES_KEY_BUF[SYMMETRIC_KEY_BYTES];

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int bst_cmd(int argc, char** argv);
static const shell_command_t shell_commands[] = {
    {"bst", "Start bootstrap server for automatic client configuration", bst_cmd}, {NULL, NULL, NULL}};

/**
 * @brief Print MOTD
 *
 */
void print_motd(void) {
#ifdef DEBUG_LOG
    puts("DA246X Bootstrapper | SERVER | DEBUG");
#else
    puts("DA246X Bootstrapper | SERVER");
#endif
}

int main(void) {
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    print_motd();

    entropy_init();        // Initialize entropy source
    gen_keypair(&cparms);  // Initialize PubPriv keys
    configure_endpoint();

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run_forever(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
