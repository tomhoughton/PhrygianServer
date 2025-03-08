#include <sys/socket.h> // Import the socket api
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <map>
#include "./Routes/Route.hpp"
#include "./HttpTypes.hpp"

class PhrygianServer {
public:

    enum HeaderId {
        METHOD = 0,
        ROUTE = 1
    };

    // int to store index to the fd of the socket:
    int serverSocket;
    sockaddr_in servAddr;
    std::map<std::string, Route*> routeMap;

    PhrygianServer(int port);

    void serve();
    void handle_request();
    void parse_request();
    void respond(int clientSocket, std::string buffer);
    HttpTypes::Request decodeBuffer(std::string buffer);

    void get(std::string route);

    void addRoute(Route* route);
    void stopServer();
};
