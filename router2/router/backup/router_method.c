#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_util.h"
#include "ambitCfg.h"
#define LAN_MAC_LEN 			(6)
#define WAN_MAC_LEN 			(6)
#define SSID_MAX_SIZE           (33) 
// #define PASSPHRASE_MAX_SIZE     (65)
#define BOARDID_MAX_SIZE		(64)
// #define SN_MAX_LEN				(32)
// #define PIN_MAX_LEN				(8)
#define WL_MODE_2G              (1)
#define WL_MODE_5G              (2)

int version ( void *argv){
	printf ("Release version: %s\n", AMBIT_PRODUCT_DESCRIPTION);
	printf("           Time : %s %s\n", __DATE__, __TIME__);
	printf("                  %s/%s/%s\n", AMBIT_HARDWARE_VERSION,
                                             AMBIT_SOFTWARE_VERSION,
                                             AMBIT_UI_VERSION);
	printf("    CFE version : %s\n", BOOT_CODE_VERSION);
}
int info (void *argv) {
	int ret = 1;

	unsigned char lan_mac[LAN_MAC_LEN+1]={0};
	unsigned char wan_mac[WAN_MAC_LEN+1]={0};
	char serial_number[SN_MAX_LEN+1]={0};
	char ssid_5G[SSID_MAX_SIZE]={0};
	char ssid[SSID_MAX_SIZE]={0};
	char pin[PIN_MAX_LEN]={0};
	char preset_passphrase[PASSPHRASE_MAX_SIZE] ={0};
	char board_id[64]={0};
	
	char lan_mac_str[20]={0};
	char wan_mac_str[20]={0};
	// char llan_mac_str[20]={0};
	// char wwan_mac_str[20]={0};
	version(NULL);
	bd_read_eth_mac (lan_mac,wan_mac);
	// memset (lan_mac,0,sizeof(lan_mac));
	// strncpy (lan_mac,wan_mac,sizeof(wan_mac));
	snprintf (lan_mac_str,sizeof(lan_mac_str),"%02X%02X%02X%02X%02X%02X", 
                lan_mac[0], lan_mac[1], lan_mac[2],
                lan_mac[3], lan_mac[4], lan_mac[5]);
	// bd_read_eth_mac(wan_mac, lan_mac);
	snprintf (wan_mac_str,sizeof(wan_mac_str),"%02X%02X%02X%02X%02X%02X", 
                wan_mac[0], wan_mac[1], wan_mac[2],
                wan_mac[3], wan_mac[4], wan_mac[5]);	
	// strncpy (lan_mac,wan_mac,LAN_MAC_LEN);		
	// snprintf (lan_mac_str,sizeof(lan_mac_str),"%02X%02X%02X%02X%02X%02X", 
                // lan_mac[0], lan_mac[1], lan_mac[2],
                // lan_mac[3], lan_mac[4], lan_mac[5]-1);	
	bd_read_board_id(board_id,BOARDID_MAX_SIZE);
	ret = bd_read_sn (serial_number,SN_MAX_LEN);
	ret = bd_read_pin (pin,PIN_MAX_LEN);
	ret = bd_read_ssid(ssid, SSID_MAX_SIZE, WL_MODE_2G);
	ret = bd_read_ssid (ssid_5G,SSID_MAX_SIZE,WL_MODE_5G);
	ret = bd_read_passphrase(preset_passphrase, PASSPHRASE_MAX_SIZE,WL_MODE_2G);
	
	// printf ("whywhy\n");
	printf ("LAN MAC: %02X%02X%02X%02X%02X%02X\n", 
                lan_mac[0], lan_mac[1], lan_mac[2],
                lan_mac[3], lan_mac[4], lan_mac[5]);
	printf ("wan_mac: %s\n",wan_mac_str);
	printf ("Serial Number: %s\n",serial_number);
	printf ("Pin code: %s\n",pin);
	printf ("SSID-2G: %s\n",ssid);
	printf ("SSID-5G: %s\n",ssid_5G);
	printf ("Passphrase: %s\n",preset_passphrase);
	printf ("Board ID: %s\n",board_id);
	// printf ("lan_mac:%s \n",llan_mac_str);
	// printf ("2");
	return ret ;

}