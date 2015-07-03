#! /usr/bin/env python3

import socket
import sys
from binascii import hexlify

def ipv6_to_int(ipv6_addr):
    return int(hexlify(socket.inet_pton(socket.AF_INET6, ipv6_addr)), 16)

if __name__ == '__main__':
    if len(sys.argv) == 2:
        i = ipv6_to_int(sys.argv[1])
        print(i)
