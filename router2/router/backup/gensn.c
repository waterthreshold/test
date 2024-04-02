#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define PREFIX "FXN"
#define DASH_LEVEL  "1"
#define SUPPLIER_CODE  "1"
#define SERIAL_LENS		13
#define CHARACTER_NUM 32
#define DEBUG(fmt,args...)	do { \
								if (debug)	\
									fprintf (stdout ,fmt,##args);	\
							}while (0)
char table[CHARACTER_NUM]={0};
char SN[SERIAL_LENS+1]="ZQL2FH0000000";
int debug =0;


void get_help(char *prog){
	
	fprintf (stdout,"%s help:\n",prog);
	fprintf (stdout,"%s <opt> SERIAL_NUMBER\n",prog);
	fprintf (stdout,"-g , --generate  generate ntgear serial number\n");
	fprintf (stdout,"-s , --save save to board data\n");
	fprintf (stdout,"-h , --help print help option\n");
	exit (0);
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


int  main(int argc ,char *argv[])
{  
  int sum=0;
  int ch;
  int save=0;
  int i;
  #ifdef DUT
		memset (SN, 0 ,SERIAL_LENS);
		 bd_read_sn(SN,SERIAL_LENS);
  #endif
  
  int index =0;
  for (i=0;i<36 ;i++){ //number num add english alpha
	  if (i<=9){
		  table[index++]='0'+i;
	  }
	  else {
		if ( 'A' + i - 10 == 'I' || 'A' + i - 10 == 'Q' || 'A' + i - 10 == 'O' ||'A' + i - 10 == 'Z')
			continue;
		else 
			table[index++] = 'A' + i -10;
	  }
	  
  }
  while ((ch = getopt (argc,argv,"ghsd")) != -1){
	
	switch (ch){
		case 'g':
			memset (SN, 0 ,SERIAL_LENS);
			generate(SN,SERIAL_LENS);
			break;
		case 'h':
			get_help(argv[0]);
			break;
		case 's':
			save=1;
			break;
		case 'd':
			debug=1;
			break;
		default:
			fprintf (stderr, " invalid option -%c ",ch);
			get_help(argv[0]);
			break;
	}
  }
 
  if (argv[optind] !=NULL && strlen (argv[optind]) == SERIAL_LENS ){
	strncpy (SN,argv[optind],SERIAL_LENS);
  }
   DEBUG ("SN =%s\n",SN);
	sum = check_sn(SN);
	if (sum < 0 ){
		fprintf (stderr , "check sum error \n" );
		 exit (-1);
	}
	
	if (SN[7] == sum  ){
		
		printf ("serial Number : %s is correct!!\n",SN);
		if (save)
			bd_write_sn(SN);
	}
	else 
		printf ("serial Number : %s is wrong SN[7]=%c should be=%c !!\n",SN,SN[7],sum);
/*
  printf("sum:");
  for (i=0;i<13;i++)
  {
   if (i==7)
     printf("%c",sum);
   else
   printf("%c",SN[i]);
  }
  printf("\n");
  */
  return 0;
}

