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

#include "thread.h"
#include "net/gnrc.h"
#include "net/gnrc/udp.h"
#include "net/gnrc/pktdump.h"

#define BST_STOP_THREAD (0x4001)
#define BST_THREAD_ACK (0x1200)

#define BST_QUEUE_SIZE (8)

static uint16_t BST_PORT = 1119;
// static uint16_t SBST_PORT = 9119;

static char _stack[THREAD_STACKSIZE_MAIN];

static gnrc_netreg_entry_t server = GNRC_NETREG_ENTRY_INIT_PID(GNRC_NETREG_DEMUX_CTX_ALL,
                                                               KERNEL_PID_UNDEF);

static void *_eventloop(void *arg)
{
    (void)arg;
    msg_t msg, reply;
    msg_t msg_queue[BST_QUEUE_SIZE];

    msg_init_queue(msg_queue, BST_QUEUE_SIZE);

    while (1)
    {
        gnrc_pktsnip_t *pkt;
        msg_receive(&msg);

        // TODO: Probs better way to do this but, e.g. with msg.type but .. meh.
        if (msg.type == BST_STOP_THREAD && msg.content.value == 1)
        {
            msg_reply(&msg, &reply);
            thread_zombify();
        }

        pkt = (gnrc_pktsnip_t *)msg.content.ptr;
        printf("Received UDP packet: %d\n", msg.content.value);
        msg_reply(&msg, &reply);
        gnrc_pktbuf_release(pkt);
    }

    return NULL;
}

static void start_server(char *mode)
{
    if (server.target.pid != KERNEL_PID_UNDEF)
    {
        printf("Error: BST server already running on port %" PRIu16 "\n", server.demux_ctx);
        return;
    }

    if (strcmp(mode, "plain") != 0 && strcmp(mode, "encrypted") != 0)
    {
        printf("Error: invalid mode '%s' specified.\n", mode);
        return;
    }

    /* Start BST server, port BST_PORT */
    server.target.pid = thread_create(_stack, sizeof(_stack), THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST, _eventloop, NULL, "bst-server");
    server.demux_ctx = (uint32_t)BST_PORT;

    if (gnrc_netreg_register(GNRC_NETTYPE_UDP, &server) == 0)
    {
        printf("Success: started BST server on port %" PRIu16 "\n", BST_PORT);
    }
    else
    {
        printf("Error: Failed to start BST server on port %" PRIu16 "\n", BST_PORT);
    }
}

static void stop_server(void)
{
    msg_t msg, reply;
    msg.content.value = 1;
    msg.type = BST_STOP_THREAD;

    /* Check if BST Server is running */
    if (server.target.pid == KERNEL_PID_UNDEF)
    {
        printf("Error: BST server is not running.\n");
        return;
    }

    /* Stop BST Server */
    if (msg_send_receive(&msg, &reply, server.target.pid) == 1)
    {
        gnrc_netreg_unregister(GNRC_NETTYPE_UDP, &server);
        if (thread_kill_zombie(server.target.pid) == 1)
        {
            server.target.pid = KERNEL_PID_UNDEF;
            puts("Success: stopped BST server.");
        }
    }
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
        if (argc < 3)
        {
            printf("Usage: %s start [plain|encrypted]\n", argv[0]);
            return 1;
        }

        if (strcmp(argv[1], "start") == 0)
        {
            start_server(argv[2]);
        }
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
