/**
 * @file main.c
 * @author Johan Edman (jedma@kth.com)
 * @brief DA246X Bootstrapper client
 * @version 0.1
 * @date 2022-04-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "include/net_info.h"

int main(void) {
    puts("DA246X Bootstrapper | DEVICE");

    _print_hw_addr();
    _print_ip_addr();

    return 0;
}
