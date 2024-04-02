#include <stdio.h>
#include<string.h>
#include <stdlib.h>
int main (int argc  ,char* argv []){
	if ( argc != 3 ){
		perror ("Need two paramater input and output path");
		exit (127);
	}	
	char path_utf16[64]={0};
	char path_ascii[64]={0};

	strncpy (path_utf16,argv[1],sizeof(path_utf16));
	strncpy (path_ascii,argv[2],sizeof(path_ascii));




	FILE* fp = NULL;
    FILE* fp_w =NULL;
	if ( (fp = fopen (path_utf16,"rb")) ==NULL) {
		perror("open failed error (1)");
	}
	if ( (fp_w = fopen (path_ascii,"w")) ==NULL) {
		perror("open failed error (2)");
	}
	unsigned char byte2[2]={0};
	fread(byte2 , 2,1 ,fp);

		printf("%x %x\n",byte2[0],byte2[1]);
	if ( byte2[0] == 0xFF && byte2[1]==0xFE){
		printf("%x %x\n",byte2[0],byte2[1]);
		while ( fread(byte2,2,1,fp)  > 0 ) {
			if (byte2[1] == 0x00 ){
				printf("%c",byte2[0]);
				fputc (byte2[0],fp_w);
			} else {
				printf ("something wrong detect");
			}

		}
	} else {
		exit (127);
	}	
	if (fp)
	   fclose(fp);
	if (fp_w)
 		fclose(fp_w);			
	return 0;
}
