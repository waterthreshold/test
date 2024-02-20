#!/bin/sh
upload_file()
{
	src=$1
	dst=$2
	tftp -p -l $src -r $dst $IP
	[ "$?" -eq "0" ] && return 1 || return 0
}
die ()
{
	msg=$1
	echo $msg
	exit 127
}

ping_test()
{
	ping -c 1 $IP  
	[ "$?" -ne "0" ] && die "Cannot ping to $IP"
}
files=$(ls /data -1A | grep -E "debug-*")
IP="10.0.0.100"
PREFIX_PATH="/data"
ping_test 
for file in $files
do
	SRC_PATH=${PREFIX_PATH}/${file}
	if [ -e "${SRC_PATH}" ]; then 
		upload_file "${SRC_PATH}" "${file}"
		[ "${REMOVE}" = "1" ] && rm ${SRC_PATH}
	fi	 
done 	
