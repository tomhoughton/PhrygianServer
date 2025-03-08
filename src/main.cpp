#include <_stdio.h>
#include <string>
#include <sys/socket.h> // Import the socket api
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "HttpTypes.hpp"
#include "PhrygianServer.hpp"
#include "./Routes/Route.hpp"
#include <sys/signal.h>
#include <iostream>

int main() {
    PhrygianServer serv(8080);

    // GET REQUEST:

    Route* root = new Route("/", [](int socket, HttpTypes::Request request) {
        std::cout << "Root" << std::endl;

        std::string response = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 4\r\n"
            "\r\n"
            "root";

        send(socket, response.c_str(), response.size(), 0);
    });
    serv.addRoute(root);

    Route* hello = new Route("/hello", [](int socket, HttpTypes::Request request) {
        std::cout << "Request object" << std::endl;

        std::cout << request.method << std::endl;
        std::cout << request.route << std::endl;

        // We need our response here:
        std::string response = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 11\r\n"
            "\r\n"
            "Hello World";

        send(socket, response.c_str(), response.size(), 0);
    });
    serv.addRoute(hello);
    serv.serve();
}
