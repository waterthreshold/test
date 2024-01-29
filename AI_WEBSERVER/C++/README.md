Sure! Here's a simple example of a web server using C++:

```cpp
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Bind the socket to a specific IP and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    
    // Listen for incoming connections
    listen(serverSocket, 5);
    
    std::cout << "Server is running on port 8080..." << std::endl;
    
    while (true) {
        // Accept a client connection
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        
        // Read client request
        char buffer[1024];
        recv(clientSocket, buffer, sizeof(buffer), 0);
        
        // Send response to client
        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
        send(clientSocket, response.c_str(), response.size(), 0);
        
        // Close the client socket
        close(clientSocket);
    }
    
    // Close the server socket
    close(serverSocket);
    
    return 0;
}
```

To build and run the web server, you can follow these steps:

1. Save the code in a file named `server.cpp`.
2. Open a terminal and navigate to the directory where `server.cpp` is located.
3. Compile the code using the command: `g++ -o server server.cpp`.
4. Run the server using the command: `./server`.

Now, the web server should be running on port 8080. You can access it by opening a web browser and entering `http://localhost:8080` in the address bar. You should see the response "Hello World!" displayed in the browser.

Note: This is a basic example for learning purposes. In a real-world scenario, you would need to handle multiple client connections, parse HTTP requests, and generate appropriate responses.
