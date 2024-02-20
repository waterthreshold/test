#!/bin/sh
IP="192.168.7.1"
USERNAME="admin"
PASSWORD="Password123"
GROUP="DeviceConfig"
METHODNAME="SOAPLogin"
ACTION_HEADER="urn:NETGEAR-ROUTER:service:${METHODNAME}:1#${GROUP}"
[ -e "cookie" ] && COOKIE=`cat cookie` || COOKIE=""

setup_ntgrHDR(){
GROUP=$1
METHODNAME=$2
ACTION_HEADER="urn:NETGEAR-ROUTER:service:${METHODNAME}:1#${GROUP}"
}

SOAP_gettype_request (){
setup_ntgrHDR  $1 $2
echo "-----send request ${ACTION_HEADER}------------"
RESULT=$(curl --silent -X POST -k https://${USERNAME}:${PASSWORD}@${IP}/soap/server_sa --data "@./SOAP/getdevice.xml" -H "SOAPACTION:${ACTION_HEADER}" -H "Cookie: ${COOKIE}" 2>&1 | tee result.txt | grep -Po '<ResponseCode>\K.*?(?=</ResponseCode>)')

[ ${RESULT} -eq 401  ] && login_request || cat result.txt 
#curl -X POST -k https://${USERNAME}:${PASSWORD}@${IP}/soap/server_sa --data "@./SOAP/getdevice.xml" -H "SOAPACTION:${ACTION_HEADER}" -H "Cookie: ${COOKIE}"
echo "---------------------------------"
}

login_request (){
setup_ntgrHDR "DeviceConfig" "SOAPLogin"
echo "--------------------SOAP LOGIN ---------------"
curl -v --silent -X POST -k https://${USERNAME}:${PASSOWRD}@${IP}/soap/server_sa --data "@./SOAP/login.xml" -H "SOAPACTION:${ACTION_HEADER}" 2>&1 | grep "Set-Cookie" | cut -d: -f 2 > cookie 
COOKIE=`cat cookie` 
echo "--------------------SOAP LOGIN END $?---------------"
}


[ -z "${COOKIE}" ] && login_request


SOAP_gettype_request "DeviceInfo" "GetInfo"
SOAP_gettype_request  "DeviceConfig" "GetQoSEnableStatus"

