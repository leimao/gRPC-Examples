# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(grpc-greetings)

add_executable(greetings_server greetings_server.cc)
target_link_libraries(greetings_server PUBLIC greetings.grpc)

add_executable(greetings_client greetings_client.cc)
target_link_libraries(greetings_client PUBLIC greetings.grpc)
