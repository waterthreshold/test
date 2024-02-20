#!/bin/sh
PROGRAM_NAME=$0
METHOD=$1
VERSION="1.0"
CONFIG_FILE="DUT_config.json" 
die () {
	msg=$1
	echo "$msg"
	exit -1 
}

check_prerequisite() {
local command="jq"
for c in command; 
do 
done 
}
load_config (){
	if [ ! -e ${CONFIG_FILE} ];then
		IP="192.168.1.1"
		USERNAME="admin"
		PASSWORD="password"

	else 
			IP=$( jq -r .ip ${CONFIG_FILE})
			USERNAME=$( jq -r .username ${CONFIG_FILE})
			PASSWORD=$( jq -r .password ${CONFIG_FILE})
	fi	
	
}
help (){
	echo "${PROGRAM_NAME} Version: ${VERSION}"
	echo "For Netgear Router ODM router(Foxconn) "
	echo -e "\nusage:\n"
	echo -e  "\tmethod:\n"

	echo "attachdev - list all device connected to DUT"
	echo "upgrade - upgrade specific firmware file to  DUT"
	echo "restoreCFG - use specif"
   	echo "loaddefault - DUT restore to initial setting "	
	echo "backCfg - Export currently profile of DUT"
	echo "help - show this program usage"
}
load_config ()
case ${METHOD} in
	attachdev)
		show_attachdev()
		;;	
