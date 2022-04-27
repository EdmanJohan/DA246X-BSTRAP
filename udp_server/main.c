#include "net/sock/tcp.h"

#define SOCK_QUEUE_LEN (1U)

sock_tcp_t sock_queue[SOCK_QUEUE_LEN];
uint8_t buf[128];

int main(void) {
    sock_tcp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_tcp_queue_t queue;

    local.port = 12345;

    if (sock_tcp_listen(&queue, &local, sock_queue, SOCK_QUEUE_LEN, 0) < 0) {
        puts("Error creating listening queue");
        return 1;
    }
    puts("Listening on port 12345");
    while (1) {
        sock_tcp_t *sock;

        if (sock_tcp_accept(&queue, &sock, SOCK_NO_TIMEOUT) < 0) {
            puts("Error accepting new sock");
        } else {
            int read_res = 0;

            puts("Reading data");
            while (read_res >= 0) {
                read_res = sock_tcp_read(sock, &buf, sizeof(buf),
                                         SOCK_NO_TIMEOUT);
                if (read_res <= 0) {
                    puts("Disconnected");
                    break;
                } else {
                    int write_res;
                    printf("Read: \"");
                    for (int i = 0; i < read_res; i++) {
                        printf("%c", buf[i]);
                    }
                    puts("\"");
                    if ((write_res = sock_tcp_write(sock, &buf,
                                                    read_res)) < 0) {
                        puts("Errored on write, finished server loop");
                        break;
                    }
                }
            }
            sock_tcp_disconnect(sock);
        }
    }
    sock_tcp_stop_listen(&queue);
    return 0;
}
