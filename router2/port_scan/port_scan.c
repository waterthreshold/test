#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#define NVRAM_IP "172.18.40.19"
int main (int argc ,char * argv[]){
	int port= atoi (argv[2]);
	struct sockaddr_in sa;
	strncpy ((char *) &sa,"", sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_port =htons( port);
	inet_aton(argv [1] , &sa.sin_addr.s_addr);
	int s = socket (AF_INET ,SOCK_STREAM,0);
	if (s< 0 ){
		perror ("failed create socket");
		exit (-1);
	}
	int err = connect (s,(struct sockaddr *) &sa, sizeof sa);
	if (err < 0){
		printf ("connect %d failed\n",port);
		exit(-1);
	}
	else {
		printf ("connect %d OK\n",port);

	}
	close (s);
	return 0 ;
}

