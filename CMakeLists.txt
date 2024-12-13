cmake_minimum_required(VERSION 3.29)
project(FinalProject)

set(CMAKE_CXX_STANDARD 26)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(client client.cpp)
target_link_libraries(client ${OpenCV_LIBS})

add_executable(server server.cpp)
target_link_libraries(server ${OpenCV_LIBS})
