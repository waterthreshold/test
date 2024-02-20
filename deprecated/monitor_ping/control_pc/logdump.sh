#!/bin/sh
while true;
do 
echo "=======wl0 dump hwa=============="
wl -i wl0 dump hwa -b pp -r 
echo "=======wl1 dump hwa=============="
wl -i wl1 dump hwa -b pp -r 
echo "=======wl2 dump hwa=============="
wl -i wl2 dump hwa -b pp -r 
uptime 
dpi status
sleep 10
done 

