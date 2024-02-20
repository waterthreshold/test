#!/bin/sh
USERNAME="admin"
PASSWORD="password"
IP="192.168.1.1"
BACKUPCFG=$1
die (){
	echo "must to bring firmware path in parameter 1 and check the file exist!!"
	exit 255;
}
[ -z $1 ] && die
[ ! -e $1 ] && die 
COOKIE=$(curl -X GET -u admin:password http://192.168.1.1/ADV_home2.htm --head  --silent  | grep "Set-Cookie:" | awk '{print $2}' )
TOKEN=$(curl -u ${USERNAME}:${PASSWORD} http://${IP}/BAK_backup.htm  --cookie "${COOKIE}" | grep "backup.cgi" |  grep -Po 'id=\K.*?(?=")'  )
echo $TOKEN
echo $COOKIE
#COOKIE="XSRF_TOKEN=1222440606;"
#curl -X POST  -F 'mtenFWUpload=@/home/jeff/Downloads/1.c' http://${USERNAME}:${PASSWORD}@${IP}/upgrade_check.cgi?${TOKEN} 
result=$(curl  -X POST --cookie "${COOKIE}"   -F "mtenBcmRestoreCfg=@${BACKUPCFG}"  http://${USERNAME}:${PASSWORD}@${IP}/backup.cgi?id=${TOKEN} )
echo "result=$result"
#curl --cookie "${COOKIE}" http://${USERNAME}:${PASSWORD}@${IP}/LGO_logout.htm > /dev/null
#curl -X POST --cookie "${COOKIE}" http://${USERNAME}:${PASSWORD}@${IP}/logout.cgi?${TOKEN} 
#if [ -n "$result" ]; then 
#sleep 1
#curl -X POST --cookie "$COOKIE" -d "Yes=Yes" http://${USERNAME}:${PASSWORD}@${IP}/upgrade.cgi?${TOKEN} --cookie "${COOKIE}"
#fi

