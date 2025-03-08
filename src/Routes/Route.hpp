#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <functional>
#include "../HttpTypes.hpp"

// https://stackoverflow.com/questions/6610046/stdfunction-and-stdbind-what-are-they-and-when-should-they-be-used

class Route {
public:
    typedef std::function<void(int, HttpTypes::Request)> RouteCallback;

    std::string route;
    RouteCallback callback;

    Route(std::string route, RouteCallback callback);
    void triggerCallback(int socket, HttpTypes::Request);

    std::string getRoute();
};

#endif // ROUTE_HPP
