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

### RPL Configuration
Unless RPL routing is already provided from elsewhere, it can be configured on the `bst_server`.

1. Check interface to configure
```sh
> ifconfig
Iface  7  HWaddr: 02:63  Channel: 26  Page: 0  NID: 0x23  PHY: O-QPSK

          Long HWaddr: FC:C2:3D:00:00:01:82:63
          TX-Power: 0dBm  State: IDLE  max. Retrans.: 3  CSMA Retries: 4
          AUTOACK  ACK_REQ  CSMA  L2-PDU:102  MTU:1280  HL:64  RTR
          RTR_ADV  6LO  IPHC
          Source address length: 8
          Link type: wireless
          inet6 addr: fe80::fec2:3d00:1:8263  scope: link  VAL
          inet6 group: ff02::2
          inet6 group: ff02::1
          inet6 group: ff02::1:ff01:8263
          inet6 group: ff02::1a
```

i.e. interface `7`.

- Initalize RPL in all nodes:
```sh
rpl init 7
```

- Configure RPL root w. global IPv6 address:
```sh
ifconfig 7 add 2001:db8::1
```

- Start the routing and generation of RPL DODAG w:
```sh
rpl root 1 2001:db8::1
```

### Start BST process
On the server node,
```sh
bst start [plain|encrypted]
```
