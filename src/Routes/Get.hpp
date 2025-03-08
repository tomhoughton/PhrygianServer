#ifndef GET_HPP
#define GET_HPP

#include "./Route.hpp"

class Get : public Route {
    void triggerCallback(int socket);
};

#endif
