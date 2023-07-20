cmake_minimum_required(VERSION 3.25)
project(MemQB)

set(CMAKE_CXX_STANDARD 17)

add_library(
        MemQB
        src/services/GraphDB.cpp
)

target_include_directories(
        MemBQ
        PUBLIC
        src/include
)

target_link_libraries(
        MemQB
        PUBLIC
        mgclient
)