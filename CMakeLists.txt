cmake_minimum_required(VERSION 3.25)
project(MemQB)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_CPP_BINDINGS ON)

add_subdirectory(ext/json)
add_subdirectory(ext/mgclient)

add_library(
        MemQB
        src/services/GraphDB.cpp
        src/MemQB.cpp)

target_include_directories(
        MemQB
        PUBLIC
        src/include
)

target_link_libraries(
        MemQB
        PUBLIC
        mgclient_cpp
        nlohmann_json
)