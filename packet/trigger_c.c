#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

	if ( argc < 2) {
		printf ("Please input one parameter\n");
		return 0;
	}
    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }


    // Message to be sent
    const char *message = argv[1];

    // Send the message to the server
    if (sendto(sockfd, message, strlen(message), 0,
               (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the server.\n");

    // Close the socket
    close(sockfd);

    return 0;
}
