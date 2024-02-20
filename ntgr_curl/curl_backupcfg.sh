#!/bin/sh
USERNAME="admin"
PASSWORD="Password123"
IP="192.168.7.1"
MODEL_NAME=$2
BACKUPCFG=$1
die (){
	echo "must to bring firmware path in parameter 2 and check the file exist!!\n 1: backup file name \n 2:device model name: RAXE500"
	exit 255;
}
[ -z $1 ] && die
[ "$#" -ne "2" ] && die  
COOKIE=$(curl -X GET -u admin:password http://192.168.1.1/ADV_home2.htm --head  --silent  | grep "Set-Cookie:" | awk '{print $2}' )
TOKEN=$(curl -u ${USERNAME}:${PASSWORD} http://${IP}/BAK_backup.htm  --cookie "${COOKIE}" | grep "backup.cgi" |  grep -Po 'id=\K.*?(?=")'  )
echo $TOKEN
echo $COOKIE
curl -X GET  http://${USERNAME}:${PASSWORD}@${IP}/NETGEAR_${MODEL_NAME}.cfg --output $BACKUPCFG
echo "done "
