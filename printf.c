#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
int main (){
	int i =0 ;
	while (i++ < 100 ){
		if (i%2!=0)
			printf("/\b");
		else 
			printf("\\\b");
		fflush (stdout);
		usleep(100000);
	}
	return 0;
}
