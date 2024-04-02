#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "action.h"
#define PIN_LEN 8
extern int gen_after_setting;
char* gen_pin (int *val ){
	srand (time (NULL));
	unsigned int x = rand () % 10000000 ;
	int sum =0;
	unsigned int tmp = x;
	int multiplethree=1;
//	printf ("%u\n",tmp);
	while (tmp > 0 ){
		int n = tmp %10;
		tmp /= 10;
		if ( multiplethree== 1) {
			n = n * 3; 
			multiplethree =0;
		}
		else {
			n = n * 1;
			multiplethree =1;
		}
		sum += n;
	}
	unsigned int last_digit = 10 -  (sum %10);
	unsigned int pin = x *10 + (last_digit % 10);
	char *pin_str = (char *) malloc (PIN_LEN+1);
	memset (pin_str,0,PIN_LEN+1);
	// printf("%08u\n",pin);
	snprintf (pin_str,PIN_LEN+1,"%08d",pin);
	if (gen_after_setting > 0){
		set_pin(pin_str);
	}
	return pin_str;
}

int check_pin(char *pin){
	int count = 0;
	int sum = 0;
	char ch = *(pin + count); 
	int ret = -1;
	while (ch != '\0' ){
//	while (count < PIN_LEN ){
//		printf ("%c %d\n",ch,count );
		if (count == 7 ) {
			char cksum =10 -  (sum %10);
			cksum %= 10;
//			printf ("%d\n",cksum);
			if (cksum  == atoi(&ch) ){
				printf ("OK\n");
				ret = 1;
			} else {
				printf ("failed\n");
			}

		}
		if (count % 2 ==0)
			sum += (ch *3);
		else 
			sum += ch ;
		count ++;
	    ch = *(pin + count); 
	}
	return ret;
}

#ifdef ACOS_LIBRARY
char *get_pin () {
	

	char *pin = (char *) malloc (PIN_MAX_LEN);
	bd_read_pin (pin,PIN_MAX_LEN);
	//printf("%s\n",pin);
	return pin ;
}

int set_pin (char *set_value) {
	int ret= 0;
	char *pin = set_value;
	printf ("%s: %s\n", "pin" ,pin);
	ret = bd_write_pin(pin);
	
	return ret;
}
#endif
/*
int main (int argc ,char *argv[]) {
	
	unsigned int  pin_code  = 0;
	char *pin= (char *) malloc (sizeof (char) * PIN_LEN +1 );
	memset (pin,0, PIN_LEN+1);
	pin_code = generate_pin ();
	printf ("%08u\n",pin_code);
	snprintf  (pin,PIN_LEN +1  , "%08u", pin_code);
	int count = 0;
	int sum = 0;
	char ch = *(pin + count); 
	int ret = 1;
	while (ch != '\0' ){
//	while (count < PIN_LEN ){
//		printf ("%c %d\n",ch,count );
		if (count == 7 ) {
			char cksum =10 -  (sum %10);
			cksum %= 10;
//			printf ("%d\n",cksum);
			if (cksum  == atoi(&ch) ){
				printf ("OK\n");
				ret = 0;
			} else {
				printf ("failed\n");
			}

		}
		if (count % 2 ==0)
			sum += (ch *3);
		else 
			sum += ch ;
		count ++;
	    ch = *(pin + count); 
	}

	return ret;

}
*/