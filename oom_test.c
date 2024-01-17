#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
int main (int argc , char* argv[]){
	pid_t pid = fork();
	if (pid < 0 ) {
		perror("fork failed");
		exit (EXIT_FAILURE);
	} 

	if (pid > 0 ) {
		printf ("parent process, child PID: %d\n",pid);
		exit(EXIT_SUCCESS);
	}
	int i = 0;
	while (++i) {
/*		int *ptr = malloc (1024 * 1024 );
		if (ptr == NULL){
			printf ("Out of Memory error occured. \n");
			break;
		} else {
			printf ("%d: malloc 1 MB\n",i);
		}
		*/
		void *mem = mmap (NULL,1024 *1024 , PROT_READ | PROT_WRITE ,MAP_ANONYMOUS | MAP_PRIVATE ,-1 ,0);
		if (mem == MAP_FAILED) {
			perror("mmap failed ");
			break;
		}
		sleep(1);

	}
	return 0;
}
