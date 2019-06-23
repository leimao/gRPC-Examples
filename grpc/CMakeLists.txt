# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(grpc-cpp-examples)

# Set examples list
set(examples greetings arithmetics)

# Make sure the generated proto header and source files are visible to the other projects
include_directories(${CMAKE_BINARY_DIR}/protos)

foreach(example ${examples})
    add_subdirectory(${example})
endforeach()
