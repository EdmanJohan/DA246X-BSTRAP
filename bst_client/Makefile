APPLICATION = bst_clientice
BOARD ?= native
TAP ?= tap1
RIOTBASE ?= $(CURDIR)/../RIOT

# Shorten default TCP timeouts to speedup testing
MSL_MS ?= 5000
TIMEOUT_MS ?= 15000

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

# RPL Modules
USEMODULE += gnrc_rpl
USEMODULE += auto_init_gnrc_rpl
# USEMODULE += dhcpv6_client_auto_init

# EEPREG
USEMODULE += eepreg

# Crypto Modules
USEPKG += c25519
USEMODULE += hashes
USEMODULE += cipher_modes
USEMODULE += crypto_aes_128

CFLAGS ?= -g -O3 -Wall -Wextra
CFLAGS += -DLOG_LEVEL=LOG_NONE

CFLAGS += '-DTHREAD_STACKSIZE_MAIN=(THREAD_STACKSIZE_DEFAULT + 1024)'
CFLAGS += -DCONFIG_ENTROPY_SOURCE_ADC_HMIN=65536

ifeq ($(BOARD),avr-rss2)
    CFLAGS += -DAVR_RSS2

    # Specific AVR modules
    USEMODULE += gnrc_sixlowpan

    # ADC Entropy
    USEMODULE += fmt
    USEMODULE += entropy_source_adc_noise
endif

ifeq ($(ENABLE_DEBUG),true)
    CFLAGS += -DDEBUG_LOG

    # Optional modules
    USEMODULE += gnrc_icmpv6_echo
    USEMODULE += shell
    USEMODULE += shell_commands
    USEMODULE += ps
    USEMODULE += od
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
ifeq ($(BOARD),native)
  ifndef CONFIG_KCONFIG_USEMODULE_SHELL
    CFLAGS += -DCONFIG_SHELL_NO_ECHO
  endif
endif

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
