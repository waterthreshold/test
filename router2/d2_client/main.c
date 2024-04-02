#include <stdlib.h>
#include <stdio.h>
#include <d2lib/d2api.h>
#define DAL2_DEFAULT_SOCKNAME "/tmp/d2/sock"
void dal_cb_recevie_events(const char * tbl, int index, const char * fld, void * up){
	printf("dal_cb_handler: tbl: %s, index: %d, fld: %s ,up =%s\n", tbl, index, fld, (char* )up);
	
}
int main (int argc , char *argv[]){
	void* d2h = NULL;
	int type;
	char *xtra=NULL;
	int i = 0;
	unsigned int maxlen=0; 
	d2h=d2_init_ex(DAL2_DEFAULT_SOCKNAME);
	printf ("result=%s\n",d2_error_string(d2_get_fieldinfo(d2h,"geNEral",0,"DeviceModel",&type,&maxlen,xtra,0))); // Case Non-sensitive
	char *device_model = malloc (maxlen);
	d2_get_string (d2h,"general",0,"DeviceModel",device_model,maxlen);
	printf ("%d, %u %s\n",type,maxlen,device_model);
	if(device_model) {
		free(device_model);
	}
	d2_subscribe(d2h,"general",true);
	d2_subscribe_cb(d2h,dal_cb_recevie_events,"4");
	for (i=0;i<8; i++){
		char * filedname=malloc(64);
		memset(filedname,0,64);
		d2_get_fieldinfo_byindex(d2h,"general",0,i,&type,&maxlen,filedname,64,xtra,0);
		printf ("%s\n",filedname);
	}
	while (1){
		
		sleep(1);
	}
	d2_destroy(d2h);
	return 0;
}