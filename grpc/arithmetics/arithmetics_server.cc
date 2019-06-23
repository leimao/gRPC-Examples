#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "arithmetics.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using arithmetics::TwoValueRequest;
using arithmetics::OneValueReply;
using arithmetics::Arithmetics;

// Logic and data behind the server's behavior.
class ArithmeticsServiceImpl final : public Arithmetics::Service {
    Status Add(ServerContext * context, const TwoValueRequest * request, OneValueReply * reply) override {
        reply->set_c(request->a() + request->b());
        return Status::OK;
    }
    Status Minus(ServerContext * context, const TwoValueRequest * request, OneValueReply * reply) override {
        reply->set_c(request->a() - request->b());
        return Status::OK;
    }
    Status Multiply(ServerContext * context, const TwoValueRequest * request, OneValueReply * reply) override {
        reply->set_c(request->a() * request->b());
        return Status::OK;
    }
    Status Divide(ServerContext * context, const TwoValueRequest * request, OneValueReply * reply) override {
        reply->set_c(request->a() / request->b());
        return Status::OK;
    }
};


void RunServer() {
    std::string server_address("0.0.0.0:50051");
    ArithmeticsServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with clients. 
    // In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. 
    // Note that some other thread must be responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char ** argv) {
    RunServer();
    return 0;
}

