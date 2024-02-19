#!/bin/sh
iptables -t nat -A PREROUTING -p tcp --dport 9999 -j DNAT --to 192.168.1.1:80
iptables -t nat -A POSTROUTING -p tcp --dport 80 --dst 192.168.1.1 -j MASQUERADE

#open the inbound port 9999  redirect postrouting 192.168.1.1 port 80
