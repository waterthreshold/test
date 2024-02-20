#!/bin/sh
model=$(curl http://192.168.1.1/currentsetting.htm | grep "Model" | cut -d'=' -f 2 | tr -d "\r" )
version=$(curl http://192.168.1.1/currentsetting.htm | grep "Firmware" | cut -d'=' -f 2  | tr -d "\r") 
DIR_NAME=${model}_${version}_OVPNPROFILE

[ ! -e "${DIR_NAME}" ] && mkdir ${DIR_NAME}
COOKIE=""
get_cookies(){
COOKIE=$(curl -u admin:password http://192.168.1.1/ADV_home2.htm --head --silent  |  grep "Set-Cookie:" | awk '{print $2}' )
}
curl --cookie "${COOKIE}" http://admin:password@192.168.1.1/nonwindows.zip --output ${DIR_NAME}/nonwindows.zip
curl --cookie "${COOKIE}" http://admin:password@192.168.1.1/windows.zip --output ${DIR_NAME}/windows.zip
curl --cookie "${COOKIE}" http://admin:password@192.168.1.1/smartphone.zip --output ${DIR_NAME}/smartphone.zip

