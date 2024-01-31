#!/bin/sh
wifi=`nmcli radio wifi`
if [ "$wifi" = "enabled" ]; then 
	nmcli radio wifi off
elif [ "$wifi" = "disabled" ]; then
	nmcli radio wifi on 
fi
		

