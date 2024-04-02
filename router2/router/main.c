#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "action.h"

char* get(int argc ,char **key);
char* burn(int argc, char **valuefw_name);
char* gen(int argc, char** dummy);
char* usage (int argc , char **es);
char* show_all (int argc, char **es);
char* version(int argc,char** dummuy2);
char* check (int argc,char** dummuy2);

typedef  struct __method{
	char *name;
	char *description;
	char* (*func) (int,char **);
	enum ARGUMENT_REQUIRE para;
}METHOD_T;

typedef struct __devinfo{
	char *name;
	char *description;
	char* (*_get) ();
	int (*_set) (char *);
	char* (*_gen)();
	int (*_check)(char *);
}INFO_T;

METHOD_T method_o [] = {
	{"get", "get the item value",&get,1},	
    {"burn", "set the item value",&burn,1},	
	{"gen", "auto generate item value",&gen,1},	
	{"check","check the value is valid format for item",&check ,1},
	{"info", "show all the item value",&show_all,0},	
    {"version", "show fw version",&version,0},	
    {"help", "print usage",&usage, 0},	
	{NULL,NULL,NULL,NULL_ARGUMENT_REQUIRE}
};

INFO_T item_o[]= {
	{"pin", "WPS pin number matched use",&get_pin,&set_pin,&gen_pin,&check_pin},
	{"sn",  "Production serial number",&get_sn,&set_sn,&gen_sn,&check_sn},
	{"ssid", "Wifi ssid 2.4G",&get_ssid,&set_ssid,&gen_ssid,NULL},
	{"ssid5g", "Wifi ssid 5G",&get_ssid5G,&set_ssid5G,&gen_ssid5G,NULL},
	{"pass", "Wifi password",&get_pass,&set_pass,&gen_pass,NULL},
	{"pass5g", "Wifi 5G band password",&get_pass5g,&set_pass5g,&gen_pass,NULL},		
	{"mac", "Ethernet mac address",&get_mac,&set_mac,&gen_mac,NULL},
	{"sku", "burn region area",&get_sku,&set_sku,NULL,NULL},
	{"boardid", "Board hardware ID",&get_boardid,&set_boardid,NULL,&check_board},
	{NULL,NULL,NULL,NULL,NULL,NULL}
};


char* get (int argc , char** items){
	
	char *item = items[0];
	//printf("argc=%d argv=%s\n",argc ,items[0]);
	int i = 0;
	while (item_o[i].name) {
		if ( strcmp (item_o[i].name, item) == 0 ){
			if (item_o[i]._get != NULL) {
				char *value = item_o[i]._get();
				printf ("%s: %s\n",item_o[i].name, value);

			} else {
				printf ("item not defined!!\n");
			}

			break;
		}
		i++;
	}
	return NULL;
}
char* burn(int argc, char **argv){
	int i =0 ;
	int ret =0;
	char *key = argv[0];
	char *value = argv[1];
	while (item_o[i].name) {
		if ( strcmp (item_o[i].name, key) == 0 ){
			if (item_o[i]._set != NULL) {
				int ret = item_o[i]._set(value);
				if (ret > 0) {
					printf("setting successful!!\n");
				}

			} else {
				printf ("item not defined!!\n");
			}

			break;
		}
		i++;
	}
	
	return ret;
}


char* gen(int argc , char** items){
	char *item = items[0];
	//printf("argc=%d argv=%s\n",argc ,items[0]);
	int i = 0;
	while (item_o[i].name) {
		if ( strcmp (item_o[i].name, item) == 0 ){
			if (item_o[i]._gen != NULL) {
				char *value = item_o[i]._gen();
				printf ("%s: %s\n",item_o[i].name, value);

			} else {
				printf ("item not defined!!\n");
			}

			break;
		}
		i++;
	}
	return NULL;
}

char* check(int argc , char** argv){
	int i =0 ;
	int ret =0;
	char *key = argv[0];
	char *value = argv[1];

	while (item_o[i].name) {
		if ( strcmp (item_o[i].name, key) == 0 ){
			if (item_o[i]._check != NULL) {
				int ret = item_o[i]._check(value);
				if (ret > 0) {
					printf("key %s, value:%s: is Valid\n",key,value);
				} else  {
					printf("key %s, value:%s: is Unvalid\n",key,value);
				}

			} else {
				printf ("item not defined!!\n");
			}

			break;
		}
		i++;
	}
	
	return ret;
}


char* usage (int argc, char **es){
	int i=0;
	
	printf ("usage: router [method] [item]\n");
	printf ("\tmethod:\n");
	while (method_o[i].name){
		printf("\t\t%s: %s\n", method_o[i].name, method_o[i].description  );
		i++;
	}
	printf ("\titem:\n");
	i=0;
	while (item_o[i].name){
		printf ("\t\t%s: %s\n",item_o[i].name,item_o[i].description);
		i++;
	}
	return NULL;
}

char* show_all (int argc, char **dummy2){
	int i =0;
	version (NULL,NULL);
	while (item_o[i].name){
		// char *value= get (item_o[i].name, NULL);
		if (item_o[i]._get != NULL) {
			char *value= item_o[i]._get();
			printf ("%s: %s\n",item_o[i].name, value);
		} else {
			printf ("function not defined!!\n");
		}
		i++;
	}
	return NULL;
}

char* version(int argc ,char** dummuy2){

	printf ("CFE_version: %s\n",CFE_VERSION);
	printf ("FIRMWARE_VERSION: %s\n",FW_MAIN_VERSION);
	return NULL;
	
}
static void  shift(int *argc , char **argv)
{
	int i;
	if (*argc <= 1 )
		return;
	
	
	*argc = *argc -1 ;	
	for (i=0;i < *argc; i++){
		
		// strcpy (argv[i],argv[i+1]);
		argv[i]=argv[i+1];
		//printf ("%s\n",argv[i]);
	}
	//printf ("%d",*argc);
	// argv[i]=NULL;
	
}

int gen_after_setting =-1;
int main (int argc , char **argv){
	if (argc <2 ){
		printf ("please following the below method\n");
		usage (NULL,NULL);
		exit(-1);
	}
	int found = -1 ;
	int i  = 0 ;
	while ( method_o[i].name ) {
		//printf ("%s\n",method_o[i].name);
		if (strcmp (method_o[i].name , *(argv+1))==0 ) {
			if ( method_o[i].para == 0 ){
				method_o[i].func(NULL,NULL);
			} 
			else { 
				//printf ("111122221\n");
				shift(&argc, argv);
				shift(&argc, argv);
				//printf ("111111111\n");
				method_o[i].func(argc,argv);
			}
			found=0;
			break;
		}
		i++;
	}
	if (found < 0 ) {
		fprintf (stderr, "Cannot found mapping method\n");
		usage (-1, argv );
	}

	return 0;
}
