#!/bin/sh
USERNAME="admin"
PASSWORD=${PASSWORD-"password"}
SET_COOKIE=$(curl --head -s  http://${USERNAME}:${PASSWORD}@172.19.66.146:10001/UPG_upgrade.htm | grep "Set-Cookie")
SET_COOKIE=${SET_COOKIE%%;*}
SET_COOKIE=${SET_COOKIE##*:}
echo $SET_COOKIE

GET_TOKEN (){
		CSRF_TOKEN=$(curl -s  http://${USERNAME}:${PASSWORD}@172.19.66.146:10001/UPG_upgrade.htm --header "Cookie:${SET_COOKIE}"| grep -oP 'id=\K.*?(?=")') #cannot have any space in Cookie header 
		echo $CSRF_TOKEN
}
Die ()
{
	msg=$1
	echo $msg
	exit 127
}

GET ()
{
CGI_ARRAY=("GetVer.cgi" \
 	"GetDevName.cgi" \
 	"GetDashboard.cgi" \
 	"GetLan.cgi" \
 	"Getupnp.cgi" \
 	 "GetIpv6.cgi" \
 	 "GetWireless.cgi" \
 	 "GetBasether.cgi" \
 	 "GetVlanIptv.cgi" \
 	 "GetPortfowarding.cgi" \
 	 "GetWirelessAdv.cgi" \
	 "GetWifiManagement.cgi" \
	 "GetHotspot.cgi" \
     "GetSystemLog.cgi"  \
	 "GetBasEtherPppoe.cgi" \
	 "GetRouterMode.cgi"
	)
for CGI in "${CGI_ARRAY[@]}"; do
	echo "$CGI ..."
	curl -s  http://${USERNAME}:${PASSWORD}@172.19.66.146:10001/${CGI} --header "Cookie:${SET_COOKIE}" | jq -e . #cannot have any space in Cookie header 
done

}
UPGRADE (){
	id=`GET_TOKEN`
	echo "id=$id"
	[ -z "$1" ] && Die "please input firmware filename"  || FIRMWARE=$1
	curl -X POST  "http://${USERNAME}:${PASSWORD}@172.19.66.146:10001/upgrade_check.cgi?=id=${id}"  -F ""mtenFWUpload=@${FIRMWARE}"" --header "Cookie:${SET_COOKIE}"  
	
}
usage ()
{	echo "Method:"
	echo -e "\tupgrade: upgrade firmware "
	echo -e "\tget: traverse all router CGI "
}


case "$1" in 
	"upgrade")
		shift 
		UPGRADE $1
		;;
	"get")
		GET
		;;
	*)
		shift 
		[ -z "$1" ] && usage || GET $1
		;;
esac


