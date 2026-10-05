cmake_minimum_required(VERSION 3.10)
project(VectorPad_Server)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

add_executable(server src/server.cpp)
target_include_directories(server PRIVATE include)


if(WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()
