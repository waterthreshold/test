#include <stdlib.h>
#include <stdio.h>
#include <bdbroker.h>
int main (int argc , char *argv[]) {
	char *router_info=NULL;
	char *version_info=NULL;
	char *diagnosis_report=NULL;
	char *status_report=NULL;
	int res = bd_box_get_router_info(&router_info);
	if ( res < 0 ) {
		perror ("bd_box_get_router_info failed");
		exit(1);
	}
	res = bd_box_get_version_info(&version_info);
	printf ("router info:\n");
	printf ("%s\n",router_info);
	printf ("----------------------------------\n");
	printf ("version info:\n");
	printf ("%s\n",version_info);
	printf ("----------------------------------\n");
	printf ("diagnosis_report info:\n");
	bd_box_get_diagnosis_report (&diagnosis_report);
	printf ("%s\n",diagnosis_report);
	printf ("----------------------------------\n");
	printf ("status_report info:\n");
	bd_box_get_status_report(&status_report);
	printf ("%s\n",status_report);
	return 0;
}