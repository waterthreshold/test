#!/bin/sh
qsdkj acos 
HTTPD_DIR=httpd_mt
die (){
	msg=$1
	echo $msg
	exit 127
}
[  "$#" -ne 1 ] && die "Must contain a cgi name. for example. devname" 
[ ! -e "$HTTPD_DIR" ] && die "Cannot find http directory"
FILENAME_NOMENCLATURE="${1,}Cgi"
FUNCTION_NAME="${1^}CgiMain"
CGI_NAME="${1^}"
echo "${FILENAME_NOMENCLATURE} ${FUNCTION_NAME}"

MAKEFILEPATH=$HTTPD_DIR/Makefile
MAKEFILECGITEXT="${FILENAME_NOMENCLATURE}.o"
sed -i "/#ADDHERE/i OBJS += \$\(CGI_DIR\)\/${FILENAME_NOMENCLATURE}.o" $MAKEFILEPATH


ASPFILEPATH=$HTTPD_DIR/httpd_asp.c
ASPGETCGITEXT="{\"Get${1}.cgi\", get${FUNCTION_NAME}},"
ASPGETCGITEXT="{\"Set${1}.cgi\", set${FUNCTION_NAME}},"
sed -i "/\s*\/\/ADDSETCGIABOVEHERE/i \ \ \ \ {\"Set${CGI_NAME}.cgi\", set${FUNCTION_NAME}}," $ASPFILEPATH
sed -i "/\s*\/\/ADDGETCGIABOVEHERE/i \ \ \ \ {\"Get${CGI_NAME}.cgi\", get${FUNCTION_NAME}}," $ASPFILEPATH

HTTPDH_PATH=$HTTPD_DIR/httpd.h
HTTPD_TEXT="#include \"cgi/${FILENAME_NOMENCLATURE}.h\""
sed -i "/\/\/HTTPDHERE/i $HTTPD_TEXT" $HTTPDH_PATH

CGI_PATH=$HTTPD_DIR/cgi
CGICPATH=${CGI_PATH}/${FILENAME_NOMENCLATURE}.c
CGIHPATH=${CGI_PATH}/${FILENAME_NOMENCLATURE}.h
cat > $CGICPATH  << C_TEMPLATE
/***************************************************************************
***
***    Copyright 2005  Hon Hai Precision Ind. Co. Ltd.
***    All Rights Reserved.
***    No portions of this material shall be reproduced in any form without the
***    written permission of Hon Hai Precision Ind. Co. Ltd.
***
***    All information contained in this document is Hon Hai Precision Ind.  
***    Co. Ltd. company private, proprietary, and trade secret property and 
***    are protected by international intellectual property laws and treaties.
***
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "httpd.h"

int get${FUNCTION_NAME}(char *value, int bufSize){
    int ret = -1;
	char *buf;
    int status = 0;   
	cJSON *${1}_obj = cJSON_CreateObject();
		
	if (${1}_obj){
		cJSON_AddStringToObject(${1}_obj, "device_name" , acosNvramConfig_get("friendly_name"));
		buf = cJSON_PrintUnformatted(${1}_obj);
		
		if (buf) {
			strlcpy(value, buf, bufSize);
			ret = strlen (value);
			free (buf);
		} else {
			ret = -1;
		}
		cJSON_Delete (${1}_obj);

	} else {
			ret = -1;
	}
	
	return ret;	
}

STATUS set${FUNCTION_NAME}(char *content, int out)
{
 	int ret = 200;
	printf("%s\n",content);
	cJSON *${1}_obj = cJSON_Parse(content);
	if (${1}_obj){
		cJSON *name = cJSON_GetObjectItem(${1}_obj,"mqtt_host");
		if (name) {
			printf("key: %s value:%s\n",name->string,name->valuestring);
			acosNvramConfig_set("wmcd_host",name->valuestring);
		} else{
			ret = 400;
		}
		name = cJSON_GetObjectItem(${1}_obj,"name");
		if (name) {
			printf("key: %s value:%s\n",name->string,name->valuestring);
			acosNvramConfig_set("wmcd_username",name->valuestring);
		} else{
			ret = 400;
		}
		name = cJSON_GetObjectItem(${1}_obj,"name");
		if (name) {
			printf("key: %s value:%s\n",name->string,name->valuestring);
			acosNvramConfig_set("wmcd_password",name->valuestring);
		} else{
			ret = 400;
		}
		cJSON_Delete(${1}_obj);
	}
	
	cJSON *result_obj = cJSON_CreateObject();
	char *buf ;

	if (result_obj){
		cJSON_AddNumberToObject(result_obj, "result" , ret);
		buf = cJSON_PrintUnformatted(result_obj);
		if (buf) {
			SendData2Client(out ,buf,  "text/html");
			free (buf);
		}
			
		cJSON_Delete (result_obj);

	}
	if (ret == 200 ){
		acosNvramConfig_save();
	}
	return ret;
}

C_TEMPLATE

cat > $CGIHPATH  << H_TEMPLATE
#ifndef _${1^^}_CGI_H
#define _${1^^}_CGI_H

#include "shared_lib_httpd.h"
int get${FUNCTION_NAME}(char *value, int bufSize);
STATUS set${FUNCTION_NAME}(char *content, int out);
#endif
H_TEMPLATE

#MAKEFILE

