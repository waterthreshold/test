Sure! Here's a simple example of a web server using C language:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\nHello, World!";

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Read request from client
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received request:\n%s\n", buffer);

    // Send response to client
    send(new_socket, response, strlen(response), 0);
    printf("Response sent.\n");

    return 0;
}
```

To build and run the web server, follow these steps:

1. Save the code in a file named `web_server.c`.
2. Open a terminal and navigate to the directory where the file is saved.
3. Compile the code using the following command: `gcc web_server.c -o web_server`.
4. Run the server using the command: `./web_server`.
5. The server will start listening on port 8080.
6. Open a web browser and enter `http://localhost
