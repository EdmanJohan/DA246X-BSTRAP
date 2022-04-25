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

#include <stdio.h>

#include "shell.h"
#include "msg.h"

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int bst_cmd(int argc, char **argv);

static const shell_command_t shell_commands[] = {
    {"bst", "Start bootstrap server for automatic client configuration", bst_cmd},
    {NULL, NULL, NULL}};

int main(void)
{
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("DA246X Bootstrapper | SERVER");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run_forever(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
