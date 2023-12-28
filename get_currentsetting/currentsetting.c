#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 4096
void sendHttpGetRequest ( const char *host , const char *path){
	int sockfd;
	struct sockaddr_in server_addr;
	char request [MAX_BUFFER_SIZE];
	if ( (sockfd = socket (AF_INET,SOCK_STREAM,0)) <0 ){
		perror("Error creating socket");
		exit (EXIT_FAILURE);
	}
	memset (&server_addr,0 ,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (80);
	if (inet_pton(AF_INET , host ,&server_addr.sin_addr) <= 0 ){
		perror ("Error converting address");
		exit (EXIT_FAILURE);
	}	

	if (connect (sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr))<0) {
		perror ("Error connecting address");
		exit (EXIT_FAILURE);
	}
	snprintf (request , MAX_BUFFER_SIZE , "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",path,host);
	if ( write (sockfd,request,strlen (request)) < 0 ) {
		perror ("Error Sending request");
		exit (EXIT_FAILURE);
	}
	char buffer [MAX_BUFFER_SIZE];
	ssize_t byteRead;
	while ( (byteRead = read (sockfd ,buffer,sizeof(buffer)-1 )) > 0 ){
		buffer[byteRead] = '\0';
		printf ("%s",buffer);
	}
	close (sockfd);
}

int main (int argc, char **argv ){
	if ( argc != 2 ) {
		perror ("please input host address");
		exit (EXIT_FAILURE);
	}
	const char *host=argv[1];
	const char *path="/currentsetting.htm";
	sendHttpGetRequest(host,path);
	return 0;
}
