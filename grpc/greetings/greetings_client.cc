#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "greetings.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using greetings::HelloRequest;
using greetings::HelloReply;
using greetings::Greeter;

class GreeterClient {
public:
    // Constructor
    GreeterClient(std::shared_ptr<Channel> channel): stub_(Greeter::NewStub(channel)) {}
    // Assembles the client's payload, sends it and presents the response back from the server.
    std::string SayHello(const std::string & user) {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_name(user);

        // Container for the data we expect from the server.
        HelloReply reply;

        // Context for the client. 
        // It could be used to convey extra information to the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->SayHello(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply.message();
        } 
        else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return "gRPC failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> stub_;
};

void InterativeGRPC() {
    // Instantiate the client. It requires a channel, out of which the actual RPCs are created. 
    // This channel models a connection to an endpoint (in this case, localhost at port 50051). 
    // We indicate that the channel isn't authenticated (use of InsecureChannelCredentials()).
    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    while (true) {
        std::string user;
        std::cout << "Please enter your user name:" << std::endl;
        // std::cin >> user;
        std::getline(std::cin, user);
        std::string reply = greeter.SayHello(user);
        if (reply == "gRPC failed") {
            std::cout << "gRPC failed" << std::endl;
        }
        std::cout << "gRPC returned: " << std::endl;
        std::cout << reply << std::endl;
    }
}


int main() {

    InterativeGRPC();

    return 0;
}



