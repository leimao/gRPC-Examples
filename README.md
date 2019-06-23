# gRPC Examples

Lei Mao

## Introduction

gRPC is a modern open source high performance RPC framework that can run in any environment. It can efficiently connect services in and across data centers with pluggable support for load balancing, tracing, health checking and authentication. It is also applicable in last mile of distributed computing to connect devices, mobile applications and browsers to backend services. The official gRPC tutorial mainly uses `make` to compile and its `CMake` compile system is no longer working. 


In this repository, I implemented gRPC C++ examples using CMake with the best practice. I also put code comments as many as possible to make sure the code is human readable and easy to understand. Currently CMake only officially support Protobuf but not gRPC. The [FindGPRC](https://github.com/IvanSafonov/grpc-cmake-example/blob/master/cmake/FindGRPC.cmake) module for CMake was borrowed. Once CMake officially support gRPC, I will update this repository accordingly.

## Dependencies

* gRPC 1.20
* Google Protocol Buffers 3.7.0
* CMake 3.14.4+

## Files

```
.
├── cmake
│   └── FindGRPC.cmake
├── CMakeLists.txt
├── docker
│   └── grpc.Dockerfile
├── grpc
│   ├── arithmetics
│   │   ├── arithmetics_client.cc
│   │   ├── arithmetics_server.cc
│   │   └── CMakeLists.txt
│   ├── CMakeLists.txt
│   └── greetings
│       ├── CMakeLists.txt
│       ├── greetings_client.cc
│       └── greetings_server.cc
├── LICENSE.md
├── protos
│   ├── arithmetics.proto
│   ├── CMakeLists.txt
│   └── greetings.proto
└── README.md
```

## Usages

### Compile

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

All the executable files would be generated in `build/bin` directory.


### Run Examples

#### Arithmetics

In one terminal,

```bash
$ ./bin/arithmetics_server 
Server listening on 0.0.0.0:50051
```

In another terminal,

```bash
$ ./bin/arithmetics_client 
Please enter your binary arithmetic expression:
300 + 200
gRPC returned: 
500
Please enter your binary arithmetic expression:
300 - 200
gRPC returned: 
100
Please enter your binary arithmetic expression:
300 * 200
gRPC returned: 
60000
Please enter your binary arithmetic expression:
300 / 200
gRPC returned: 
1
Please enter your binary arithmetic expression:
```

#### Hello World

In one terminal,

```bash
$ ./bin/greetings_server   
Server listening on 0.0.0.0:50051
```

In another terminal,

```bash
$ ./bin/greetings_client 
Please enter your user name:
Lei Mao
gRPC returned: 
Hello Lei Mao!
Please enter your user name:
Michael Jordan
gRPC returned: 
Hello Michael Jordan!
Please enter your user name:
Kobe Bryant
gRPC returned: 
Hello Kobe Bryant!
Please enter your user name:
```

## Notes

Users may also use the gRPC Dockerfile provided to create a Docker container to reproduce.
