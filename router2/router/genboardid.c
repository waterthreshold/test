
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "action.h"
#define MAX_BOARDID_SIZE 64
static int check_format (char *U12,char *H, char *T, char *netgear) {
	int ret =1;
	if (strncmp (U12,"12",2)!=0 || strlen (U12) != 2 ){
		ret =0;
		goto FAILED;
	}
	if ( strlen (H) != 3 ){
		ret =0;
		goto FAILED;
	}
	if (strlen (T) != 2 ){
		ret =0;
		goto FAILED;
	}
	if (strncmp (netgear,"NETGEAR",strlen ("NETGEAR")) !=0 || strlen ("NETGEAR") != strlen(netgear) ){
		ret =0;
		goto FAILED;
	}
	
FAILED:
	return ret;
}
int check_board(char *in_boardid){
	int ret = -1 ;
	char  dummy[4][32]={0};
	// char in_boardid[32]={0};
	// strncpy (in_boardid,ori_boardid,32);
	// printf ("%s\n",ori_boardid);
	if (sscanf (in_boardid,"U%[0-9]H%[0-9]T%[0-9]_%s",dummy[0],dummy[1],dummy[2],dummy[3]) != 4 ){
		
		//perror ("detect wrong boardid format, please check ex. U12H425T20_NETGEAR" );
		ret=-1;
	} else {
		printf("%s %s %s %s",dummy[0],dummy[1],dummy[2],dummy[3]);

		ret = check_format(dummy[0],dummy[1],dummy[2],dummy[3]);
	}
	return ret;
}
int set_boardid(char* in_boardid){
	char  dummy[4][32]={0};
	int ret = 1;

	if (sscanf (in_boardid,"U%[0-9]H%[0-9]T%[0-9]_%s",dummy[0],dummy[1],dummy[2],dummy[3]) != 4 ){
		printf ("Board id format wrong!!\n");
		ret=-1;
		goto L_FAILED;
	}
	// printf("%s %s %s %s",dummy[0],dummy[1],dummy[2],dummy[3]);
	if (check_format(dummy[0],dummy[1],dummy[2],dummy[3]) < 0 ){
		printf ("Board id content wrong!!\n");
		ret=-1;
		goto L_FAILED;
	}
	ret = bd_write_board_id(in_boardid);
L_FAILED:	
	return ret;
}

char* get_boardid(){
	char* ori_boardid=malloc(MAX_BOARDID_SIZE);
	bd_read_board_id (ori_boardid,MAX_BOARDID_SIZE);
	return ori_boardid;
}