#!/bin/sh
USERNAME="admin"
PASSWORD="password"
IP="192.168.1.1"
die (){
	echo "must to bring firmware path in parameter 1 and check the file exist!!"
	exit 255;
}



restore_default (){
	COOKIE=$(curl -X GET -u admin:password http://${IP}/ADV_home2.htm --head  --silent  | grep "Set-Cookie:" | awk '{print $2}' )
	TOKEN=$(curl -u ${USERNAME}:${PASSWORD} http://${IP}/BAK_backup.htm  --cookie "${COOKIE}" | grep "backup.cgi" |  grep -Po 'id=\K.*?(?=")'  )
	echo $TOKEN
	echo $COOKIE
	result=$(curl  -X POST --cookie "${COOKIE}"   -d "ROMReset=yes"  http://${USERNAME}:${PASSWORD}@${IP}/backup.cgi?id=${TOKEN} )
	echo $result
}

while [ 1 ];
do
paping ${IP} -p 80 -c 1  
[ "$?" -eq "0" ]  && sleep 1 && restore_default && break 
done 

echo "Netgear Restore default !!"
