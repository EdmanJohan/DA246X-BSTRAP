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

while getopts b:a:c:t:: flag
do
    case "${flag}" in
        b) board=${OPTARG};;
        a) application=${OPTARG};;
        c) clean=${OPTARG};;
        t) terminal=${OPTARG};;
    esac
done


if [ -z "$board" ] || [ -z "$application" ]; then
    echo "Usage: ./flash_term.sh -b [native|avr-rss2] -a [bst_dev|bst_gw] [-c [true|false] -t [true|false]]"
    exit
fi

if [ "$board" != "native" ] && [ "$board" != "avr-rss2" ]; then
    echo "Error: Invalid board '$board'."
    echo "Usage: ./flash_term.sh -b [native|avr-rss2] -a [bst_dev|bst_gw] [-c [true|false] -t [true|false]]"
    exit
else
    if [ "$board" == "native" ]; then
        port="tap"
    else
        port="tty"
    fi
fi

if [ "$application" != "bst_dev" ] && [ "$application" != "bst_gw" ]; then
    echo "Error: Invalid application '$application'."
    echo "Usage: ./flash_term.sh -b [native|avr-rss2] -a [bst_dev|bst_gw] [-c [true|false] -t [true|false]]"
    exit
else

    if [ "$application" == "bst_gw" ]; then
        if [ "$port" == "tty" ]; then
            port="/dev/ttyUSB0"
        elif [ "$port" == "tap" ]; then
            port="tap0"
        fi
    elif [ "$application" == "bst_dev" ]; then
        if [ "$port" == "tty" ]; then
            port="/dev/ttyUSB1"
        elif [ "$port" == "tap" ]; then
            port="tap1"
        fi
    fi
fi

if [ -z "$clean" ] || [ "$clean" == "false" ]; then
    echo "Compiling w. BOARD=$board, APP=$application, PORT=$port"
    if [ "$board" == "avr-rss2" ]; then
        countdown;
    fi

    echo "PORT=$port"
    BOARD=$board make all flash -C $application PORT=$port -j$NPROC
else
    BOARD=$board make clean all flash -C $application PORT=$port -j$NPROC
fi

if [ "$terminal" != "yes" ] && [ "$terminal" != "true" ]; then
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

if [ "$terminal" == "yes" ] || [ "$terminal" == "true" ]; then
    if [ "$board" == "avr-rss2" ]; then
        if [ "$application" == "bst_gw" ]; then
            minicom ttyUSB0
        elif [ "$application" == "bst_dev" ]; then
            minicom ttyUSB1
        fi
    elif [ "$board" == "native" ]; then
        BOARD=$board make term -C $application PORT=$port
    else
        exit;
    fi
else
    exit;
fi
