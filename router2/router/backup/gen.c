#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAC_LEN	12	
#define OUI_LEN 6
char NETGEAR_VENDER_OUI [][OUI_LEN+1] ={
	"00095B",
	"000FB5",
	"00146C",
	"00184D",
	"001B2F",
	"001E2A",
	"001F33",
	"00223F",
	"0024B2",
	"0026F2",
	"008EF2",
	"04A151",
	"08028E",
	"0836C9",
	"08BD43",
	"100C6B",
	"100D7F",
	"10DA43",
	"1459C0",
	"200CC8",
	"204E7F",
	"20E52A",
	"288088",
	"28C68E",
	"2C3033",
	"2CB05D",
	"30469A",
	"3498B5",
	"3894ED",
	"3C3786",
	"405D82",
	"4494FC",
	"44A56E",
	"4C60DE",
	"504A6E",
	"506A03",
	"54077D",
	"6CB0CE",
	"6CCDD6",
	"744401",
	"78D294",
	"803773",
	"80CC9C",
	"841B5E",
	"8C3BAD",
	"941865",
	"94A67E",
	"9C3DCF",
	"9CC9EB",
	"9CD36D",
	"A00460",
	"A021B7",
	"A040A0",
	"A06391",
	"A42B8C",
	"B03956",
	"B07FB9",
	"B0B98A",
	"BCA511",
	"C03F0E",
	"C0FFD4",
	"C40415",
	"C43DC7",
	"C89E43",
	"CC40D0",
	"DCEF09",
	"E0469A",
	"E046EE",
	"E091F5",
	"E4F4C6",
	"E8FCAF",
	"F87394"
};

int isHex (char c) {
	int ret=0;
	char ch = tolower (c);
	if ( (ch >='0' && ch<= '9') || (ch >= 'a' && ch <= 'f') ) {
		ret = 1;
		
	}
	return ret;
}
int genMAC (char *mac){
	int num= sizeof (NETGEAR_VENDER_OUI)/ sizeof (NETGEAR_VENDER_OUI[0]);
	time_t t ;
	srand ((unsigned ) time (&t));
	int idx =  rand() % num;
	unsigned int rand_mac =  rand() % (0xFFFFFF+1);
	 // printf ("%s %06X num =%d\n",NETGEAR_VENDER_OUI[idx],rand_mac,num );
	snprintf ( mac ,MAC_LEN+1  ,"%s%06X",NETGEAR_VENDER_OUI[idx],rand_mac);
	
}




int isvalidMAC (char *mac){
	int ret=1;
	char ch;
	int count ;
	if (strlen (mac) != MAC_LEN) {
		fprintf (stdout , "MAC : %s Error !!",mac);
		ret = 0;
		return ret;
	}
	for (count=0,ch= *(mac+count); ch !='\0'; count++ ) {
		
		if ( count >= MAC_LEN){
			// ret = 0;
			break;
		}
		ch= *(mac+count);
		printf ("%c",ch);
		if (!isHex (ch))
		{
			ret= 0; 
			break;
		}
		
	}
	return ret;
	
}


int  convert (int n) {
	// if (n < 10)
		// return '0' + n;
	// else 
		// return 'A'+ n-10;
	return table [n];
}

int  reverse_convert (int n) {
	int i;
	int ret=-1;
	for (i=0;i< CHARACTER_NUM;i++){
		if (table [i]== n){
			ret = i; 
			break;
		}
	}

	return ret;
}

int check_sn ( char *sn){
	
	int i;
	int sum=0;
	int j=12;
	for (i=0;i < SERIAL_LENS;i++)
  {
	  if (SN[i]>='a' && SN[i]<='z')
		SN[i]='A' + SN[i] -'a';
	if (i==7)
		continue; 
	
	if ( (SN[i]>='0'&& SN[i]<='9' ) || (SN[i]>='A' && SN[i]<='Z') ){
		sum+=j*reverse_convert(SN[i]);
		DEBUG ("%d*%d \n",j ,reverse_convert(SN[i]));
	}
	// else if {
		// sum+=j*reverse_convert(SN[i]);
		// printf ("%d*%d \n",j ,reverse_convert(SN[i]));
	// }
	
	// else if (SN[i]>='a' && SN[i]<='z')
		// sum+=j*(SN[i]-'a'+10);
	else {
		printf("wrong sn detct it !!\n");
		exit (-1);
	}
	j--;
  }
  DEBUG ("sum=%d\n",sum);
  sum=sum % CHARACTER_NUM;
  sum =convert (sum);
	
	return sum ;
	
}


int generate ( char *sn, int len ){
	int ret =0;
	time_t t;
	struct tm tmb;
	int year;
	int i;
	int m;
	// strcat (sn , PREFIX);
	// strcat (sn , DASH_LEVEL);
	time(&t);
	char random_str[8]={0};
	srand(time(NULL));
	
	localtime_r (&t, &tmb);
	year = tmb.tm_year +1900 - 2010 ;
	m = tmb.tm_mon + 1;
	m = convert (m);
	
	year = convert (year);
	
	for (i =0 ; i < 6 ; i++){
		int a = rand()%CHARACTER_NUM;
		a = convert (a);
		char buf[8]={0};
		snprintf (buf ,sizeof (buf) , "%c",a);
		strcat (random_str,buf);
	}
	DEBUG ("year=%d month=%d rand_str=%s\n",year,m,random_str);
	snprintf (sn,len+1,"%s%s%c%c%s%s",PREFIX,DASH_LEVEL,year,m,SUPPLIER_CODE,random_str);
	printf ("Generate sn =%s\n",sn);
	int sum = check_sn (sn);
	sn[7]=sum;
	return ret;
}

