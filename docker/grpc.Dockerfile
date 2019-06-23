# gRPC Dockerfile
# Usage
# docker build -f grpc.Dockerfile [--build-arg NPROCS=$(nproc)] [--tag=grpc-cmake] .
ARG NPROCS=1

FROM ubuntu:18.04

LABEL maintainer="Lei Mao <dukeleimao@gmail.com>"

# If we echo ARGs, ARGs has to go after FROM
# RUN echo "=================================" &&\
#     echo "Using ${NPROCS} threads to build." &&\
#     echo "================================="

# Upgrade Ubuntu components
RUN apt-get update &&\
    apt-get install -y vim git curl &&\
    apt-get upgrade -y

# gRPC
# https://github.com/grpc/grpc/tree/master/src/cpp
# https://github.com/grpc/grpc/blob/master/BUILDING.md
RUN cd /tmp &&\
    apt-get install -y build-essential autoconf libtool pkg-config &&\
    apt-get install -y libgflags-dev libgtest-dev &&\
    apt-get install -y clang libc++-dev &&\
    git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc &&\
    cd grpc &&\
    git submodule update --init &&\
    make -j${NPROCS} &&\
    # WARNING: After installing with make install there is no easy way to uninstall, which can cause issues if you later want to remove the grpc and/or protobuf installation or upgrade to a newer version.
    make install &&\
    # Refresh shared library cache.
    ldconfig

# Protobuf
# The latest Protobuf might not be compatible with gRPC
# We always install the protobuf included in gRPC
RUN cd /tmp/grpc/third_party/protobuf &&\
    make -j${NPROCS} &&\
    make install &&\
    # Refresh shared library cache.
    ldconfig

# CMake
RUN cd /tmp &&\
    git clone https://github.com/Kitware/CMake.git &&\
    cd CMake &&\
    ./bootstrap --parallel=${NPROCS} &&\
    make -j${NPROCS} &&\
    make install

# Working directory
WORKDIR /workspace