#! /usr/bin/env python3.3

import ipaddress

ip = ipaddress.ip_address('10.1.1.1')
print(ip)

ip = ipaddress.ip_address('::10.1.1.1')
print(ip)

ip = ipaddress.IPv4Address('10.1.1.1')
print(ip)

ip = ipaddress.IPv6Address('::10.1.1.1')
print(ip)

net = ipaddress.ip_network('10.1.1.0/24')
print(net)

net = ipaddress.ip_network('::10.1.1.0/120')
print(net)

net = ipaddress.ip_network('10.1.1.1/24', False)
print(net)

host = ipaddress.ip_interface('10.1.1.1/24')
print(host)
print(host.network)