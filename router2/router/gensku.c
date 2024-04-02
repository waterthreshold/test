
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "action.h"
const char sku_name [][C_MAX_SKU_STR_SIZE] = {
	"none",
	"NA",
	"WW",
	"GR",
	"PR",
	"RU",
	"BZ",
	"IN",
	"KO",
	"JP",
	"AU",
	"CA",
	"US",
	"MX",
	"AP",
	"PA",
};
int valid_sku_input (char *str){
	int ret =-1 ;
	
	if (str ==NULL){
		return -1 ;
	}
	int total_sku  = sizeof (sku_name) / sizeof (sku_name[0]);
	int index = atoi (str);
	if (index > 0  && index <= total_sku) {
		ret =0;
	}
	return ret;
	
}
char* get_sku (){
	char* sku =  malloc(SKU_LEN);
	unsigned short region_num = 0;
	unsigned char region_code_num[8] = "";
	unsigned char lang[LANG_LEN] = "";
	unsigned char wl_region[WL_REGION_LEN] = "";
	unsigned char timezone[TIMEZONE_LEN] = "";
	
	int  ret = bd_read_sku_info(&region_num, sku, SKU_LEN, lang, LANG_LEN,
		wl_region, WL_REGION_LEN, timezone, TIMEZONE_LEN);
	//printf ("%s(%x)\n",sku,region_num);
	return sku;
}

int set_sku(char *sku ){
	int ret = -1 ;
	int i;
	for ( i = 1 ; i < sizeof (sku_name) / sizeof(sku_name[0]); i++) {
		if (strncmp (sku,sku_name[i],C_MAX_SKU_STR_SIZE) == 0) {
			ret = bd_write_sku_info(i);
			break;
		}
	}
	return ret;
}