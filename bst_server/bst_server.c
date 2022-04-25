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

static uint16_t BST_PORT = 1119;
static uint16_t SBST_PORT = 9119;

static gnrc_netreg_entry_t server = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                               KERNEL_PID_UNDEF);
static gnrc_netreg_entry_t server_secure = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                                      KERNEL_PID_UNDEF);

static void start_server(void)
{
    if (server.target.pid != KERNEL_PID_UNDEF || server_secure.target.pid != KERNEL_PID_UNDEF)
    {
        printf("Error: BST server already running on port %" PRIu16 " (%" PRIu32 ")\n", server.demux_ctx, server_secure.demux_ctx);
        return;
    }

    /* Start BST server, port BST_PORT */
    server.target.pid = gnrc_pktdump_pid;
    server.demux_ctx = (uint32_t)BST_PORT;
    if (gnrc_netreg_register(GNRC_NETTYPE_UDP, &server) == 0)
    {
        printf("Success: started BST server on port %" PRIu16 "\n", BST_PORT);
    }
    else
    {
        printf("Error: Failed to start BST server on port %" PRIu16 "\n", BST_PORT);
    }

    /* Start BSTS server, port SBST_PORT */
    server_secure.target.pid = gnrc_pktdump_pid;
    server_secure.demux_ctx = (uint32_t)SBST_PORT;
    if (gnrc_netreg_register(GNRC_NETTYPE_UDP, &server_secure) == 0)
    {
        printf("Success: started BST(S) server on port %" PRIu16 "\n", SBST_PORT);
    }
    else
    {
        printf("Error: Failed to start BST(S) server on port %" PRIu16 "\n", SBST_PORT);
    }
}

static void stop_server(void)
{
    /* Check if BST Server is running */
    if (server.target.pid == KERNEL_PID_UNDEF && server_secure.target.pid == KERNEL_PID_UNDEF)
    {
        printf("Error: BST server is not running.");
        return;
    }

    /* Stop BST Server */
    gnrc_netreg_unregister(GNRC_NETTYPE_UDP, &server);
    server.target.pid = KERNEL_PID_UNDEF;

    gnrc_netreg_unregister(GNRC_NETTYPE_UDP, &server_secure);
    server_secure.target.pid = KERNEL_PID_UNDEF;

    puts("Success: stopped BST server.");
}

int bst_cmd(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Usage: %s [start|stop]\n", argv[0]);
        return 1;
    }

    // Modes: plain, encrypted

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
