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

#include "include/bst_client.h"
#include "include/net_info.h"
#include "msg.h"
#include "shell.h"
#include "thread.h"

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
char line_buf[SHELL_DEFAULT_BUFSIZE];

static char client_stack[THREAD_STACKSIZE_MAIN];

int main(void) {
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("DA246X Bootstrapper | CLIENT");

    _print_hw_addr();
    _print_ip_addr();

    thread_create(client_stack, sizeof(client_stack), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, bst_client, NULL, "bst-client");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run_forever(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
