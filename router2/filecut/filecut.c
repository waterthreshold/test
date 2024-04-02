#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

void print_usage(){
	printf("filecut decription input file trucate file\n ");
	printf("-i input file (must need)\n");
	printf("-o output file (option) default stdout\n");
	printf("-s start postion (option) start from 0\n");
	printf("-f offest (option) end to EOF\n");
}



int main (int argc ,char *argv[]){
	char ch;
	char inputfile[256]={0};
	char output_name[256]={0};
	
	int offset =0;
	int start=0;
	FILE *fp=NULL,*fp_out=NULL;
	int use_stdout=0;
	int n;
	while ((ch=getopt(argc,argv ,"i:o:s:f:"))!= -1){
	 	switch (ch){
				case 'i':
						strncpy(inputfile,optarg,sizeof(inputfile));
						break;
				case 'o':
						strncpy(output_name,optarg,sizeof(output_name));
						break;
				case 's':
//						printf("s=%s\n",optarg);
						start=atoi(optarg);
						break;
				case 'f':
//						printf("f=%s\n",optarg);
						offset=atoi(optarg);
						break;
				default:
						print_usage();
						break;
			
		}
	 }

//	printf("input=%s %d %d \n",inputfile,start,offset);

	if (strlen(inputfile)<=0){
			print_usage ();
			return 0; 
	}

	fp=fopen(inputfile,"r");
	if (fp ==NULL){
		perror ("open input file:");
		exit(0);
	}
	fseek(fp,start,SEEK_SET);

	if (strlen(output_name)<=0){
		fp_out=stdout;

	}
	else {
		fp_out= fopen (output_name,"w");
		if (fp_out==NULL){
			perror("out file error:");
			exit(0);
		}
	}
	//printf ("1111111111111111\n");
	while (!feof(fp) && offset>0  ){
		fread (&ch,1,1,fp);	
		fwrite (&ch,1,1,fp_out);
		offset-=1;
	}
	if (fp!=NULL)
	fclose (fp);
	if (fp_out!=NULL)
	fclose (fp_out);
	return 0;
}
