#include "PhrygianServer.hpp"
#include <_stdio.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include "./Routes/Route.hpp"

PhrygianServer::PhrygianServer(int port) {
    // Create the socket and the address:
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // We now want to bind our socket:
    if (bind(serverSocket, (struct sockaddr*)(&servAddr), sizeof(servAddr)) < 0) {
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }

    // Finally make it listen:
    if (listen(serverSocket, 100) < 0) {
        perror("Couldn't listen");
        exit(EXIT_FAILURE);
    }
}

void PhrygianServer::serve() {
    std::cout << "Server listening" << std::endl;
    while (true) {

        // Create the client socket:
        sockaddr_in clientAddr;
        socklen_t client_len = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &client_len);

        // Create our in buffer:
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);

        std::cout << "-- connection: "
            << clientAddr.sin_port
            << " "
            << inet_ntoa(clientAddr.sin_addr)
            << "--"
            << std::endl;

        std::cout << "--- Buffer ---" << std::endl;
        std::cout << buffer << std::endl;

        respond(clientSocket, buffer);

        // Here we would need to send some sort of event:
    }
}

HttpTypes::Request PhrygianServer::decodeBuffer(std::string buffer) {
    HttpTypes::Request req;

    // Create a stream for the buffer:
    std::istringstream buffStream(buffer);

    std::string currLine;
    int counter = PhrygianServer::HeaderId::METHOD;
    while (getline(buffStream, currLine, '\n')) {
        if (currLine.empty() || currLine == "\r") { break; } // End of header.

        // We also need to split according to spaces:
        std::istringstream innerBuff(currLine);
        std::string innerLine;
        while(getline(innerBuff, innerLine, ' ')) {
            if (!innerLine.empty()) {
                switch (counter) {
                    case PhrygianServer::HeaderId::METHOD:
                        req.method = innerLine;
                    case PhrygianServer::HeaderId::ROUTE:
                        req.route = innerLine;
                }
            }
            counter++;
        }
    }

    return req;
}

void PhrygianServer::respond(int clientSocket, std::string buffer) {

    // Decode the buffer:
    HttpTypes::Request request = decodeBuffer(buffer);

    auto routesIt = routeMap.find(request.route);
    if (routesIt == routeMap.end()) {
        perror("ROUTE DOES NOT EXIST");
        exit(EXIT_FAILURE);
    }

    Route* route = routesIt->second;
    route->triggerCallback(clientSocket, request);
}

void PhrygianServer::addRoute(Route* route) {
    routeMap[route->getRoute()] = route;
}

void PhrygianServer::stopServer() { close(serverSocket); }
