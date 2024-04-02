#ifndef __ROUTER_ACTION__
#define  __ROUTER_ACTION__

#define CFE_VERSION "V1.1.1.1"
#define FW_MAIN_VERSION  "1.1.1.1"
#define FW_SUB_VERSION "1.1.1" 

#define LAN_MAC_LEN 			(6)
#define WAN_MAC_LEN 			(6)
#define SSID_MAX_SIZE           (33) 
#define PASSPHRASE_MAX_SIZE     (64)
#define BOARDID_MAX_SIZE		(64)
#define SN_MAX_LEN				(32)
#define PIN_MAX_LEN				(8)

#define C_MAX_KEY_STR_SIZE                  (32)
#define C_MAX_SKU_STR_SIZE                  (8)

#define WL_MODE_2G              (1)
#define WL_MODE_5G              (2)


#define SKU_LEN             8
#define LANG_LEN            32
#define WL_REGION_LEN       4
#define TIMEZONE_LEN        8


enum ARGUMENT_REQUIRE{
	NULL_ARGUMENT_REQUIRE =-2 ,
	NONE_ARGUMENT_REQUIRE =-1,
	PROGRAM_ARGUMENT_REQUIRE,
	ONE_ARGUMENT_REQUIRE ,
	MULTI_ARGUMENT_REQUIRE
}; 

char *get_pin () ;
int set_pin (char *set_value);
char *gen_pin () ;
int check_pin (char *set_value);

char *get_sn () ;
int set_sn (char *set_value);
char *gen_sn () ;
int check_sn (char *set_value);

char *get_ssid () ;
int set_ssid (char *set_value);
char *get_ssid5G () ;
int set_ssid5G (char *set_value);
char *gen_ssid () ;
char *gen_ssid5G () ;



char* gen_pass();
char *get_pass () ;
int set_pass (char *set_value);

char *get_pass5g () ;
int set_pass5g (char *set_value);

char *get_boardid () ;
int set_boardid (char *set_value);
int check_board(char* boardid);
char *get_sku() ;
int set_sku(char *set_value);
char* gen_mac();
char *get_mac() ;
int set_mac(char *set_value);

#endif