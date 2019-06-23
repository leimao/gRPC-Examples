# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(grpc-examples)

# C++ Standard
add_compile_options(-std=c++11)

# Set gRPC CMake module
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Not useful in this example
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Optional
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(protos)
add_subdirectory(grpc)