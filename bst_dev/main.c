#include <stdio.h>

#include "include/net_info.h"

int main(void) {
    puts("RIOT network stack example application");

    _print_hw_addr();
    _print_ip_addr();

    return 0;
}
