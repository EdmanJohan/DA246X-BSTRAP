APPLICATION = bst_device
BOARD ?= native
RIOTBASE ?= $(CURDIR)/../RIOT

DEVELHELP ?= 1
QUIET ?= 1

USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_netif_single
USEMODULE += gnrc_ipv6

# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo
# Use minimal standard PRNG
USEMODULE += prng_minstd

CFLAGS += -DLOG_LEVEL=LOG_NONE
CFLAGS += -DCONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF=2 \
          -DGNRC_NETIF_IPV6_GROUPS_NUMOF=2 -DCONFIG_GNRC_IPV6_NIB_NUMOF=1 \
          -DCONFIG_GNRC_IPV6_NIB_OFFL_NUMOF=1

include $(RIOTBASE)/Makefile.include

