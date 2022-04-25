/**
 * @file bst.c
 * @author Johan Edman (jedma@kth.se)
 * @brief
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "net/gnrc.h"
#include "net/gnrc/udp.h"

#include "net/gnrc/pktdump.h"

static gnrc_netreg_entry_t server = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                               KERNEL_PID_UNDEF);

static void start_announce(void)
{
}

static void start_server(void)
{
    uint16_t port = 9200;

    if (server.target.pid != KERNEL_PID_UNDEF)
    {
        printf("Error: server already running on port %" PRIu32 "\n", server.demux_ctx);
        return;
    }

    // TODO: Start server, register on chosen port
    server.target.pid = gnrc_pktdump_pid;
    server.demux_ctx = (uint32_t)port;
    gnrc_netreg_register(GNRC_NETTYPE_UDP, &server);

    printf("Success: started BST server on port %" PRIu16 "\n", port);
}

static void stop_server(void)
{
    /* Check if BST Server is running */
    if (server.target.pid == KERNEL_PID_UNDEF)
    {
        puts("Error: Server was not running.");
        return;
    }

    /* Stop BST Server */
    gnrc_netreg_unregister(GNRC_NETTYPE_UDP, &server);
    server.target.pid = KERNEL_PID_UNDEF;
    puts("Success: stopped BST server.");
}

int bst_cmd(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Usage: %s [start|stop]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0)
    {
        start_server();
    }
    else if (strcmp(argv[1], "stop") == 0)
    {
        stop_server();
    }
    else
    {
        puts("Error: invalid command.");
    }

    return 0;
}
