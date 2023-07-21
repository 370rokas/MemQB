cmake_minimum_required(VERSION 3.25)
project(MemQB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

set(BUILD_CPP_BINDINGS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(ext/json)
add_subdirectory(ext/mgclient)

add_library(MemQB
        src/MemQB/MemQB.cpp
        src/DBWrapper/GraphDB.cpp
        src/Parsers/csv/csv.cpp
        src/Handlers/csvHandler.cpp src/Handlers/csvHandler.hpp src/MemQB/QueryBuilder.cpp src/MemQB/QueryBuilder.hpp)

add_executable(MemQBTest src/main.cpp)

target_include_directories(MemQB PUBLIC
        src/
)

target_link_libraries(MemQB PUBLIC
        mgclient_cpp
        nlohmann_json
)

target_link_libraries(MemQBTest PUBLIC MemQB)

# cppcheck
find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
        message("-- cppcheck found!")
        list(
                APPEND CMAKE_CXX_CPPCHECK
                "--enable=warning"
                "--inconclusive"
                "--force"
                "--inline-suppr"
        )
else()
        message(FATAL_ERROR "-- Failed to find cppcheck binary. Please add it to path/install it.")
endif()