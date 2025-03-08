#include "Route.hpp"
#include <_stdio.h>
#include <string>

Route::Route(std::string route, RouteCallback callback)
    : route(route), callback(callback) {}

void Route::triggerCallback(int socket, HttpTypes::Request request) {
    callback(socket, request);
}

std::string Route::getRoute() { return route; }
