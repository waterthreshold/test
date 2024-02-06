#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
 int calculate_checksum (char *s, int size ) {
	 int c0=0 , c1=0;
	int i;
	for (i=0;i<size;i++){
		c0 +=(s[i] & 0xff);
		c1 += c0;
	}
	int b = ( c0 & 65535 ) + ((c0>>16) & 65535);
	c0 = (( b >> 16) + b) & 65535;

	b= (c1 & 65535) + ((c1 >>16) & 65535);
	c1 = ((b >> 16) + b) & 65535;
	
	 int checksum = ((c1<<16) | c0);
	return checksum;

}
int main (int argc , char* argv[]) {
	FILE *fp=NULL;
	struct stat s;
	if (argc != 2 ){
		perror ("Must input file name !!");
		exit(127);
	}
	if ( (fp=fopen(argv[1],"r")) ==NULL ){
		perror("Cannot open file successfully");
		exit(127);
	}
	int size ;
	if ( stat(argv[1], &s) ==0){
		size = s.st_size;
	} else {
		perror("stat");
	}
	char *buf = (char *) malloc (size);
	int n =fread (buf ,1 ,size,fp);
	//printf ("n=%d size=%d\n",n,size);
	unsigned int result =calculate_checksum(buf,size);
	//printf ("%s checksum: %08X (%u)\n",argv[1],result,result);
	printf ("%u\n",result);
	if (buf)
		free(buf);
	if (fp)
		fclose(fp);
	return 0;
}
