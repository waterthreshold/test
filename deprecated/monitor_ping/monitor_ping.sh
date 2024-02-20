#!/bin/sh
failed_func () {
#	zenity --info --text="Failed ping occurs"
	echo "detect ping failed `date +"%Y/%m/%d-%H:%M:%S"`" | tee -a ping_result
#	exit 127
}

[ ! -e "ping_result" ] && touch ping_result || rm ping_result;touch ping_result
while  true 
do
	ping -q  www.google.com -c 1 
	[ "$?" -ne 0 ] && failed_func
	sleep 1 
done 
