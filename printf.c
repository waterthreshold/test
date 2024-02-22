#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
int main (){
	int i =0 ;
	while (i++ < 100 ){
		if (i%3==1)
			printf("%d%%... /\r",i);
		else if (i%3==2)
			printf("%d%%... -\r",i);
		else
			printf("%d%%... \\\r",i);
		fflush (stdout);
		usleep(100000);
	}
	return 0;
}
