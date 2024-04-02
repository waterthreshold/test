#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DHCPIP_MODE		0
#define STATICIP_MODE	1 


typedef struct dhcp_lease{
	unsigned char mac[16];
	unsigned char ip [4];
	unsigned char leasetime[4];
	unsigned char hostname[64];
}T_dhcpInfo;


int listdhcpmode(){
	int ret =STATICIP_MODE;
	FILE *fp=NULL;
	int n=0;
	if ((fp=fopen ("/tmp/udhcpd.leases","rb"))== NULL){
		fprintf (stderr,"[%s] openfile error!!\n",__func__);
		ret =-1;
		return ret;
	} 
	T_dhcpInfo dhcpinfo;

	while (  !feof(fp) ){
		char MAC[18]={0};
		fread( &dhcpinfo,sizeof (T_dhcpInfo),1,fp );
		if (ferror(fp))
			break;
		printf ("T_dhcpInfo size:%d\n",sizeof(T_dhcpInfo));
		snprintf (MAC,sizeof(MAC),"%02X:%02X:%02X:%02X:%02X:%02X",dhcpinfo.mac[0],dhcpinfo.mac[1],
																dhcpinfo.mac[2],dhcpinfo.mac[3],
																dhcpinfo.mac[4],dhcpinfo.mac[5]);
		/*if (strncmp (MAC ,g_device_tbl.MAC[index],sizeof (MAC)) == 0)
		{
			ret=DHCPIP_MODE;
			break;
		}*/
		
		unsigned int leasetime= dhcpinfo.leasetime[0]<<24 | dhcpinfo.leasetime[1]<<16 | dhcpinfo.leasetime[2]<< 8| dhcpinfo.leasetime[3] ;
		printf ("mac=%s, hostname=%s lease_time=%d\n",MAC,dhcpinfo.hostname,leasetime);
	}
	
	if (fp)
		fclose(fp);

	return ret;
}

int main (){
	listdhcpmode ();
}