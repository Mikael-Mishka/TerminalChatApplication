#include <iostream>

// Network things
#include <netinet/in.h> // AF_INET
#include <sys/socket.h> // Socket
#include <unistd.h> // Read function
#include <arpa/inet.h> // For inet_addr for client

#include "client.hpp"
#include "server.hpp"



int main() {

    std::string user_input;

    std::cout << "[s]/[c]";
    std::cin >> user_input;

    if(user_input == "s") {
        Server::run_server();
        return 0;
    }

    else if(user_input == "c"){
        Client::run_client();
        return 0;
    }

    else {
        std::cout << "ERROR: BAD INPUT!";
    }

    return 0;
}


