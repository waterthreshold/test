#!/bin/sh
USERNAME="admin"
PASSWORD="password"
IP="192.168.1.1"
LANIP=192.168.1.1
NETMASK=255.255.255.0
default_cookie="XSRF_TOKEN=1222440606"
die (){
	echo "must to bring firmware path in parameter 1 and check the file exist!!"
	exit 255;
}



set_lanip (){
	COOKIE=$(curl -X GET -u admin:password http://${IP}/BAS_ether.htm --head  --silent  | grep "Set-Cookie:" | awk '{print $2}' )
	[ -z ${COOKIE} ] && COOKIE=${default_cookie}
	TOKEN=$(curl -u ${USERNAME}:${PASSWORD} http://${IP}/BAK_backup.htm  --cookie "${COOKIE}" | grep "backup.cgi" |  grep -Po 'id=\K.*?(?=")'  )
	echo $TOKEN
	echo $COOKIE
	result=$(curl  -X POST --cookie "${COOKIE}"   -d "action=Apply&device_name=RAXE500&sysLANIPAddr1=192&sysLANIPAddr2=168&sysLANIPAddr3=99&sysLANIPAddr4=1&sysLANSubnetMask1=255&sysLANSubnetMask2=255&sysLANSubnetMask3=255&sysLANSubnetMask4=0&rip_direction=1&sysRIPVersion=Disabled&sysRIPAuthMode=No+authentication&sysRIPPass=&sysRIPKey=&dhcp_server=dhcp_server&sysPoolStartingAddr4=2&sysPoolFinishAddr4=254&select=-1&arp_enable=disable&ipmac_token=0&dev_name=RAXE500&lan_ipaddr=192.168.99.1&lan_netmask=255.255.255.0&rip_enable=0&rip_multicast=1&rip_version=2&rip_auth_mode=md5&rip_auth=0&rip_auth_string=&rip_key_string=&lan_proto=dhcp&dhcp_start=192.168.99.2&dhcp_end=192.168.99.254&dhcp_start_old=10.0.0.2&dhcp_end_old=10.0.0.254&pptp_wan_ipaddr=...&l2tp_wan_ipaddr=...&pppoe_wan_ipaddr=...&pptp_serv_ipaddr=10.0.0.138&l2tp_serv_ipaddr=&wan_dns1_pri=&wan_dns1_sec=&wan_proto=dhcp&wan_ipaddr=192.168.7.17&wan_netmask=255.255.255.0&repeater=&repeater_an=&dlna_autoip_en=0&tmp_lan_ipaddr=0.0.0.0&tmp_lan_netmask=0.0.0.0&tmp_lan_proto=null&tmp_rip_enable=null"  http://${USERNAME}:${PASSWORD}@${IP}/lan.cgi?id=${TOKEN} )
	echo $result
}

if [ $# -eq 3 ]; then 
	LANIP=$1
	NETMASK=$2
fi 

set_lanip



