cmake_minimum_required(VERSION 3.10)

# Set the project name:
project(CppHttp)

# Set the c++ standard:
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable:
add_executable(CppHttp src/Routes/Route.cpp src/Routes/Get.cpp src/PhrygianServer.cpp src/main.cpp)

add_executable(Client src/client.cpp)
