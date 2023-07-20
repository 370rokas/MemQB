cmake_minimum_required(VERSION 3.25)
project(TestParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestParser src/main.cpp src/services/GraphDB.cpp src/services/GraphDB.hpp)

target_link_libraries(TestParser
        PUBLIC
        mgclient
        )