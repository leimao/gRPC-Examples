# gRPC Examples

## Introduction

gRPC C++ examples built with CMake.

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

### Build Docker Image

```bash
$ docker build -f docker/grpc.Dockerfile --build-arg GPRC_VERSION=1.34.0 --build-arg NUM_JOBS=8 --tag grpc-cmake:1.34.0 .
```

To build for different gRPC versions and use different number of CPU threads, please change the values in the build arguments.


### Run Docker Container

Two separate Docker containers should be started for the gRPC server and the gRPC client.

```bash
$ docker run -it --rm --network host -v $(pwd):/mnt grpc-cmake:1.34.0
```

### Build Examples

```bash
$ cmake -B build
$ cmake --build build --config Release --parallel
```

All the executable files would be generated in `build/grpc` directory.

### Run Examples

#### Arithmetics

In one terminal, we start the gRPC server.

```bash
$ ./build/grpc/arithmetics/arithmetics_server
Server listening on 0.0.0.0:50051
```

In another terminal, we start the gRPC client.

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

In one terminal, we start the gRPC server.

```bash
$ ./build/grpc/greetings/greetings_server 
Server listening on 0.0.0.0:50051
```

In another terminal, we start the gRPC client.

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

### References

* [gRPC Tutorial](https://leimao.github.io/blog/gRPC-Tutorial/)
