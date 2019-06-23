#include <iostream>
#include <memory>
#include <string>

#include <cstdio>
#include <vector>

#include <grpc++/grpc++.h>

#include "arithmetics.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using arithmetics::TwoValueRequest;
using arithmetics::OneValueReply;
using arithmetics::Arithmetics;

class ArithmeticsClient {
public:
    // Constructor
    ArithmeticsClient(std::shared_ptr<Channel> channel): stub_(Arithmetics::NewStub(channel)) {}
    // Assembles the client's payload, sends it and presents the response back from the server.
    std::string Compute(int a, int b, char op) {
        // Data we are sending to the server.
        TwoValueRequest request;
        request.set_a(a);
        request.set_b(b);

        // Container for the data we expect from the server.
        OneValueReply reply;

        // Context for the client. 
        // It could be used to convey extra information to the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status;
        if (op == '+') {
            status = stub_->Add(&context, request, &reply);
        }
        else if (op == '-') {
            status = stub_->Minus(&context, request, &reply);
        }
        else if (op == '*') {
            status = stub_->Multiply(&context, request, &reply);
        }
        else if (op == '/') {
            status = stub_->Divide(&context, request, &reply);
        }
        else {
            std::cout << "Invalid operator!" << std::endl;
        }

        // Act upon its status.
        if (status.ok()) {
            return std::to_string(reply.c());
        } 
        else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<Arithmetics::Stub> stub_;
};

void InterativeGRPC() {
    // Instantiate the client. It requires a channel, out of which the actual RPCs are created. 
    // This channel models a connection to an endpoint (in this case, localhost at port 50051). 
    // We indicate that the channel isn't authenticated (use of InsecureChannelCredentials()).
    ArithmeticsClient calculator(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    while (true) {
        std::string expression;
        // std::cout << "Please enter your binary arithmetic expression (please do not use space):" << std::endl;
        // std::cin >> expression;
        std::cout << "Please enter your binary arithmetic expression:" << std::endl;
        std::getline(std::cin, expression);
        std::vector <std::string> tokens;

        std::size_t prev = 0, pos;
        char op;
        while ((pos = expression.find_first_of("+-*/", prev)) != std::string::npos)
        {
            op = expression[pos];
            if (pos > prev) {
                tokens.push_back(expression.substr(prev, pos - prev));
            }
            prev = pos + 1;
        }
        if (prev < expression.length())
        {
            tokens.push_back(expression.substr(prev, std::string::npos));

        }
        if (tokens.size() != 2) {
            std::cout << "The binary arithmetic expression has to have exactly three tokens!" << std::endl;
            continue;
        }

        int a = std::stoi(tokens[0]);
        int b = std::stoi(tokens[1]);
        // std::cout << a << op << b << std::endl;
        std::string reply = calculator.Compute(a, b, op);
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
