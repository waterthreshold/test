#!/bin/sh
USERNAME="admin"
PASSWORD="password"
IP="192.168.1.1"
FIRMWARE=$1
die (){
	echo "must to bring firmware path in parameter 1 and check the file exist!!"
	exit 255;
}
[ -z $1 ] && die
[ ! -e $1 ] && die 
COOKIE=$(curl -u ${USERNAME}:${PASSWORD} http://${IP}/ADV_home2.htm --head --silent  | grep "Set-Cookie:" | awk '{print $2}' )
TOKEN=$(curl -u ${USERNAME}:${PASSWORD} http://${IP}/UPG_upgrade.htm  --cookie "${COOKIE}" | grep "upgrade_check.cgi" |  grep -Po 'id=\K.*?(?=")'  )
echo $TOKEN

#curl -X POST  -F 'mtenFWUpload=@/home/jeff/Downloads/1.c' http://${USERNAME}:${PASSWORD}@${IP}/upgrade_check.cgi?${TOKEN} 
result=$(curl --retry 3 --connect-timeout 10  -X POST  -F ""mtenFWUpload=@${FIRMWARE}"" http://${USERNAME}:${PASSWORD}@${IP}/upgrade_check.cgi?${TOKEN} --cookie "${COOKIE}" | grep "YesButton")
echo "result=$result"
if [ -n "$result" ]; then 
sleep 1
curl -X POST --cookie "$COOKIE" -d "Yes=Yes" http://${USERNAME}:${PASSWORD}@${IP}/upgrade.cgi?${TOKEN} --cookie "${COOKIE}"
fi
