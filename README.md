# DA246X Code Repository

## Quickstart
Either perform any of the following commands,

Compile target `avr-rss2`:
```sh
BOARD=avr-rss2 make all flash term -C bst_server PORT=/dev/ttyUSB0
```

```sh
BOARD=avr-rss2 make all flash term -C bst_client PORT=/dev/ttyUSB1
```

Compile target `native`:
```sh
make all flash term -C bst_server PORT=tap0
```

```sh
make all flash term -C bst_client PORT=tap1
```

Or run:
```sh
./flash_term.sh -b [native|avr-rss2] -a [bst_client|bst_server] [-c true]
```
