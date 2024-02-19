#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#define DEBUG
float THRESHOLD= 95;
int g_annoucement =0;

int getIPAddress(const char *interfaceName, char *ipAddress, size_t ipAddressSize) {
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return -1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) continue;

        if (strcmp(ifa->ifa_name, interfaceName) == 0) {
            if (ifa->ifa_addr->sa_family == AF_INET) { // IPv4 address
                struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
                inet_ntop(AF_INET, &(addr->sin_addr), ipAddress, ipAddressSize);
                freeifaddrs(ifaddr);
                return 0;
            }
        }
    }

    freeifaddrs(ifaddr);
    return -1; // Interface not found or doesn't have an IPv4 address
}

void daemonize() {
    // Fork off the parent process
    pid_t pid = fork();

    // An error occurred
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Create a new session ID for the child process
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }
	#ifndef DEBUG
	 	close(STDIN_FILENO);
    	close(STDOUT_FILENO);
    	//close(STDERR_FILENO);	
		open("/dev/null", O_RDWR);
    	dup(0);
    	dup(0);
	#endif

}


int post_message (char *message ){
    CURL *curl;
    CURLcode res;
	cJSON *root=NULL;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt (curl,CURLOPT_POST,1L);
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json"); // Replace with your access token
		
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		char *post_data ;
		root =  cJSON_CreateObject();
		cJSON_AddStringToObject (root ,"type", "message");
		cJSON *attachments = cJSON_CreateArray();
		cJSON *attachment_item = cJSON_CreateObject ();
		cJSON_AddStringToObject(attachment_item,"contentType","application/vnd.microsoft.card.adaptive");
		cJSON *content = cJSON_CreateObject();
		cJSON_AddStringToObject(content , "type","AdaptiveCard");
		cJSON *bodys = cJSON_CreateArray();
	   	cJSON *body1 = cJSON_CreateObject();
		cJSON_AddStringToObject(body1,"type","TextBlock");
		cJSON_AddStringToObject(body1,"text",message);	
		cJSON_AddItemToArray (bodys,body1);
		cJSON_AddItemToObject (content,"body",bodys);
		cJSON_AddStringToObject(content , "$schema","http://adaptivecards.io/schemas/adaptive-card.json");
		cJSON_AddStringToObject(content , "version","1.0");
		cJSON_AddItemToObject(attachment_item,"content",content);
		cJSON_AddItemToArray(attachments, attachment_item);
		cJSON_AddItemToObject(root, "attachments",attachments);

		post_data=cJSON_Print(root);
		printf("JSON Data:\n%s\n", post_data);

    // Free cJSON resources

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup and release resources
        curl_easy_cleanup(curl);
    	cJSON_Delete(root);
    	free(post_data);	
    }

    return 0;
	
} 
float check_disk_usage (char *path){
   		struct statvfs stat;
		float n = 0 ;
		if (statvfs(path, &stat) == 0) {
			unsigned long long total_space = stat.f_blocks * stat.f_frsize;
			unsigned long long free_space = stat.f_bfree * stat.f_frsize;
			unsigned long long used  =  total_space - free_space;
			n = ((float) used/ (float) total_space ) * 100;
			printf("Total space: %llu bytes\n", total_space);
			printf("Free space: %llu bytes\n", free_space);
			printf("Available space: %llu bytes\n", used);
		} else {
			perror("Error");
		}
	return n;
}

void print_usage (){
	fprintf (stderr, "-t interval check time for seconds default 300 (5 mins)\n");
	fprintf (stderr, "-p monitor system path available usage default \"/\"\n");
	fprintf (stderr, "-i to input a specific interface to fetch the server ip default eth0\n");
	fprintf (stderr, "-g the threshold\n");
}

int main(int argc , char *argv[]) {
	char opt ; 
	char path[32]="/";
	int  interval=300;
	float usage;
	char interface[128]= "eth0";
	char message[1024]={0};
		
	while ((opt=getopt(argc ,argv , "i:t:p:g:"))!= -1 ) {
		switch (opt) {
			case 't':
				interval = atoi(optarg);	
				break;
			case 'p':
				strncpy (path, optarg ,sizeof (path));
				break;
			case 'i':
				strncpy (interface,optarg,sizeof(interface));
				break;
			case 'g':
				THRESHOLD=atof(optarg);
				break;
			default:
				print_usage();
				exit (0);
				break;
				
		}
	} 
	daemonize();
	
	while (1) {
		usage = check_disk_usage (path);
			printf ("%f!\n",usage);
		if (g_annoucement && usage < THRESHOLD) {
			g_annoucement =0;
		}
		if ( usage > THRESHOLD && g_annoucement==0){
			printf ("alarm!!\n");
			 char ipAddress[INET_ADDRSTRLEN];
			 if (getIPAddress(interface, ipAddress, sizeof(ipAddress)) == 0) {
     			   printf("IP address of %s: %s\n", interface, ipAddress);
    		} else {
       			 strncpy (ipAddress,interface,sizeof(ipAddress));

   	 		}
			
			snprintf (message , sizeof (message),"The %s server the space utilization reaches %.2f, it is necessary to promptly clear unnecessary file!",ipAddress,usage);
			
			post_message(message);
			g_annoucement =1; 
		}
	
		sleep (interval);	
	}

    return 0;
}
