#include "action.h"

//pin
char *get_pin () {
	#if 1 
	char *pin= "123123123";
	#else 
	char *pin = (char *) malloc (PIN_MAX_LEN);
	bd_read_pin (pin,PIN_MAX_LEN);
	#endif
	return pin ;
}
int *set_pin (char *set_value) {
	int ret= 0;
	char *pin = set_value;
	#if 1
		printf ("%s: %s", "pin" ,pin);
	#else
		ret = bd_write_pin(pin);
	#endif
	return ret;
}

//sn
char *get_pin () {
	#if 1 
	char *sn= "123123123";
	#else 
	char *sn = (char *) malloc (PIN_MAX_LEN);
	bd_read_pin (pin,PIN_MAX_LEN);
	#endif
	return pin ;
}
int *set_pin (char *set_value) {
	int ret= 0;
	char *pin = set_value;
	#if 1
		printf ("%s: %s", "pin" ,pin);
	#else
		ret = bd_write_pin(pin);
	#endif
	return ret;
}
char *get_ssid () {
	#if 1 
	char *ssid= "123123123";
	#else 
	char *ssid = (char *) malloc (PIN_MAX_LEN);
	bd_read_pin (ssid,PIN_MAX_LEN);
	#endif
	return ssid ;
}
int *set_pin (char *set_value) {
	int ret= 0;
	char *pin = set_value;
	#if 1
		printf ("%s: %s", "pin" ,pin);
	#else
		ret = bd_write_pin(pin);
	#endif
	return ret;
}

char* get_ssid  (){
	char *
} 

char* get_boardid () {
	char board_id[64]={0};
	
	return board_id;
} 

char* 

char* set (char *item , char ){
} 
*/