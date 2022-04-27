APPLICATION = udp_server
BOARD ?= native
TAP ?= tap0
RIOTBASE ?= $(CURDIR)/../RIOT

# Shorten default TCP timeouts to speedup testing
MSL_MS ?= 1000
TIMEOUT_MS ?= 3000

# Enable safety checking for development process, disable in production
DEVELHELP ?= 1

# Enable debug logging
ENABLE_DEBUG ?= false

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_netif_single
USEMODULE += gnrc_ipv6_default

# Include TCP/UDP Support
USEMODULE += gnrc_sock_tcp
USEMODULE += gnrc_sock_udp
USEMODULE += sock_util

USEMODULE += dhcpv6_client_auto_init

# RPL Modules
USEMODULE += sixlowpan
USEMODULE += gnrc_rpl
USEMODULE += auto_init_gnrc_rpl

# Optional modules
USEMODULE += gnrc_icmpv6_echo
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

CFLAGS += -DLOG_LEVEL=LOG_NONE
CFLAGS += -DCONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF=2 \
          -DGNRC_NETIF_IPV6_GROUPS_NUMOF=2 -DCONFIG_GNRC_IPV6_NIB_NUMOF=4 \
          -DCONFIG_GNRC_IPV6_NIB_OFFL_NUMOF=1

ifeq ($(BOARD),avr-rss2)
    CFLAGS += -DAVR_RSS2
endif

ifeq ($(ENABLE_DEBUG),true)
    CFLAGS += -DDEBUG_LOG
endif

# Enable/Disable to show compiler invocation lines
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# Set GNRC_PKTBUF_SIZE via CFLAGS if not being set via Kconfig.
ifndef CONFIG_GNRC_PKTBUF_SIZE
  CFLAGS += -DCONFIG_GNRC_PKTBUF_SIZE=512
endif

# Set CONFIG_GNRC_TCP_MSL via CFLAGS if not being set via Kconfig
ifndef CONFIG_GNRC_TCP_MSL_MS
  CFLAGS += -DCONFIG_GNRC_TCP_MSL_MS=$(MSL_MS)
endif

# Set CONFIG_GNRC_TCP_CONNECTION_TIMEOUT_DURATION via CFLAGS if not being set
# via Kconfig
ifndef CONFIG_GNRC_TCP_CONNECTION_TIMEOUT_DURATION_MS
  CFLAGS += -DCONFIG_GNRC_TCP_CONNECTION_TIMEOUT_DURATION_MS=$(TIMEOUT_MS)
endif

# Set the shell echo configuration via CFLAGS if not being controlled via Kconfig
ifndef CONFIG_KCONFIG_USEMODULE_SHELL
  CFLAGS += -DCONFIG_SHELL_NO_ECHO
endif

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
