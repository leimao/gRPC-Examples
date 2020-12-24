# Minimum CMake required
cmake_minimum_required(VERSION 3.13)

project(gRPC_CPP_Examples VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Set examples list
set(examples greetings arithmetics)

foreach(example ${examples})
    add_subdirectory(${example})
endforeach()
