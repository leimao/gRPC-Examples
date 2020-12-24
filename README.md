# gRPC Examples

Lei Mao

## Introduction

gRPC is a modern open source high performance RPC framework that can run in any environment. It can efficiently connect services in and across data centers with pluggable support for load balancing, tracing, health checking and authentication. It is also applicable in last mile of distributed computing to connect devices, mobile applications and browsers to backend services. 


## Dependencies

* gRPC 1.34
* CMake 3.13.0+

## Files

```
.
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
│   └── greetings.proto
└── README.md
```

## Usages

### Compile

```bash
$ cmake -B buil
$ cmake --build build --config Release --parallel
```

All the executable files would be generated in `build/grpc` directory.

### Run Examples

#### Arithmetics

In one terminal,

```bash
$ ./build/grpc/arithmetics/arithmetics_server
Server listening on 0.0.0.0:50051
```

In another terminal,

```bash
$ ./build/grpc/arithmetics/arithmetics_client 
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
$ ./build/grpc/greetings/greetings_server 
Server listening on 0.0.0.0:50051
```

In another terminal,

```bash
$ ./build/grpc/greetings/greetings_client 
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
