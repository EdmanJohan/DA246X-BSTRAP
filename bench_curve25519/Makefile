APPLICATION = bench_curve25519
BOARD ?= native
TAP ?= tap0
RIOTBASE ?= $(CURDIR)/../RIOT

# Enable safety checking for development process, disable in production
DEVELHELP ?= 0

USEMODULE += ztimer
USEMODULE += ztimer_usec
USEMODULE += benchmark
USEMODULE += hashes

USEPKG += c25519

# Enable debug logging
ENABLE_DEBUG ?= false

CFLAGS ?= -g -O3 -Wall -Wextra

ifeq ($(BOARD),avr-rss2)
    CFLAGS += -DAVR_RSS2
endif

# Enable/Disable to show compiler invocation lines
QUIET ?= 1

# Set the shell echo configuration via CFLAGS
ifeq ($(BOARD),native)
  ifndef CONFIG_KCONFIG_USEMODULE_SHELL
    CFLAGS += -DCONFIG_SHELL_NO_ECHO
  endif
endif

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
