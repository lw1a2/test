#!/bin/bash

iptables -A INPUT -i eth1 -p ip -j DROP
