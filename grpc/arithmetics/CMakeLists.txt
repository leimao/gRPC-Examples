# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(grpc-arithmetics)

add_executable(arithmetics_server arithmetics_server.cc)
target_link_libraries(arithmetics_server PUBLIC arithmetics.grpc)

add_executable(arithmetics_client arithmetics_client.cc)
target_link_libraries(arithmetics_client PUBLIC arithmetics.grpc)
