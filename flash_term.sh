#!/bin/bash
port=""
NPROC=$(echo "$(nproc)/2" | bc)

countdown() {
  secs=5
  shift
  while [ $secs -gt 0 ]
  do
    printf "\r\033[KPress reset in %.d seconds" $((secs--))
    sleep 1
  done
  echo
}

while getopts b:a:c:t:d:: flag
do
    case "${flag}" in
        b) board=${OPTARG};;
        a) application=${OPTARG};;
        c) clean=${OPTARG};;
        t) terminal=${OPTARG};;
        d) debug=${OPTARG};;
    esac
done


if [ -z "$board" ] || [ -z "$application" ]; then
    echo "Usage: ./flash_term.sh -b [native|avr-rss2] -a [bst_client|bst_server] [-c [true|false] -t [true|false]]"
    exit
fi

if [ "$board" != "native" ] && [ "$board" != "avr-rss2" ]; then
    echo "Error: Invalid board '$board'."
    echo "Usage: ./flash_term.sh -b [native|avr-rss2] -a [bst_client|bst_server] [-c [true|false] -t [true|false]]"
    exit
else
    if [ "$board" == "native" ]; then
        port="tap"
    else
        port="tty"
    fi
fi

if [ "$application" != "bst_client" ] && [ "$application" != "bst_server" ]; then
    echo "Error: Invalid application '$application'."
    echo "Usage: ./flash_term.sh -b [native|avr-rss2] -a [bst_client|bst_server] [-c [true|false] -t [true|false]]"
    exit
else

    if [ "$application" == "bst_server" ]; then
        if [ "$port" == "tty" ]; then
            port="/dev/ttyUSB0"
        elif [ "$port" == "tap" ]; then
            port="tap0"
        fi
    elif [ "$application" == "bst_client" ]; then
        if [ "$port" == "tty" ]; then
            port="/dev/ttyUSB1"
        elif [ "$port" == "tap" ]; then
            port="tap1"
        fi
    fi
fi

if [ "$debug" == "true" ] || [ "$debug" == "yes" ] || [ "$debug" == "1" ]; then
    debug=true
fi

echo "Compiling w. BOARD=$board, APP=$application, PORT=$port, DEBUG=$debug"
if [ "$board" == "avr-rss2" ]; then
    countdown;
fi

if [ -z "$clean" ] || [ "$clean" == "false" ]; then
    BOARD=$board make all flash -C $application PORT=$port -j$NPROC ENABLE_DEBUG=$debug
else
    BOARD=$board make clean all flash -C $application PORT=$port -j$NPROC ENABLE_DEBUG=$debug
fi

if [ "$terminal" != "true" ] && [ "$terminal" != "yes" ] && [ "$terminal" != "1" ]; then
    while true; do
        echo ""
        read -p "Open terminal? " yn
        case $yn in
            [Yy]* ) terminal=yes; break;;
            [Nn]* ) exit;;
            * ) echo "Please answer yes or no.";;
        esac
    done
fi

if [ "$terminal" == "true" ] || [ "$terminal" == "yes" ] || [ "$terminal" == "1" ]; then
    if [ "$board" == "avr-rss2" ]; then
        if [ "$application" == "bst_server" ]; then
            minicom ttyUSB0
        elif [ "$application" == "bst_client" ]; then
            minicom ttyUSB1
        fi
    elif [ "$board" == "native" ]; then
        BOARD=$board make term -C $application PORT=$port ENABLE_DEBUG=$debug
    else
        exit;
    fi
else
    exit;
fi
