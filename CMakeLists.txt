cmake_minimum_required(VERSION 3.29)
project(FinalProject)

set(CMAKE_CXX_STANDARD 26)

add_executable(FinalProject main.cpp
        protocol.hpp
        server/server.cpp
        client/client.cpp)
