#ifndef HTTPTYPES_HPP
#define HTTPTYPES_HPP

#include <string>

namespace HttpTypes {
struct Request {
    std::string method;
    std::string route;
};
} // HttpTypes
#endif
