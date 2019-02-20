#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ndbm.h>
#define BYTE_1K	1024
int main(){
	DBM *
	char a= NULL;//(const char *)0;
	printf ("%\n",a);
	char * size_block = (char *) malloc(BYTE_1K);
	sprintf (size_block,"Hello World");
	char *new_tmp= (char *)realloc (size_block ,512) ;
	printf ("size_block %d new_tmp %d\n",sizeof (size_block),sizeof (new_tmp));
	
	if (new_tmp !=NULL)
		printf ("11111=%s\n",new_tmp);
		if (size_block !=NULL)
		printf ("22222=%s\n",size_block);
	return EXIT_SUCCESS;
}