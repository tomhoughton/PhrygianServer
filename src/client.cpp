#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    std::cout << "Hello Client" << std::endl;

    // Create our socket:
    int clientSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0);

    // Create the address:
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server:
    if (connect(clientSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0){
        std::cout << "Client could not connect" << std::endl;
        return -1;
    };

    // Send data to the server:
    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    // Close our socket:
    close(clientSocket);

    return 0;
}
