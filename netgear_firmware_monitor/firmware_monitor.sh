#!/bin/sh


prerequisite_check (){
command -v jq 
[  "$?" -ne "0" ] && die "Please installl " 
}
URL_PROJECTNAME=${1,,}

firmware_version=$(curl  https://www.netgear.com/support/product/${1,,}\#download | grep "Firmware Version"  | head -n 1 | grep -Po "<h1>Firmware Version \K.*?(?=</h1>)")
#firmware_version=$(curl  https://www.netgear.com/support/product/{$1,,}\#download   )
echo $firmware_version
PROJECT_NAME="XR1000"
model_name="XR1000v2"
DOWNLOAD_PATH=${HOME}/firmware/${model_name}/${firmware_version}
[ ! -e "${DOWNLOAD_PATH}" ] && mkdir -p ${DOWNLOAD_PATH}
firmware_name=${model_name}-V${firmware_version}.zip
curl -k https://www.downloads.netgear.com/files/GDC/${PROJECT_NAME}/${firmware_name} --output ${DOWNLOAD_PATH}/${firmware_name}
unzip ${DOWNLOAD_PATH}/${firmware_name} -d ${DOWNLOAD_PATH}

