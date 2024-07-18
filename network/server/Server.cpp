#include "server.hpp"

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void Server::run_server() {

    const int SERVER_PORT = 6969;

    const int FAILURE = -1;

    int buf_size = 1024;

    char buffer[buf_size];

    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_socket_address;

    server_socket_address.sin_port = htons(SERVER_PORT);
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_addr.s_addr = INADDR_ANY;


    int result = bind(server_socket, (struct sockaddr*) &server_socket_address, sizeof(server_socket_address));

    if(result == FAILURE) {
        close(server_socket);
        std::cout << "<SERVER> Failed to bind to port on the specified adress exiting...\n";
        return;
    }

    int listen_result = listen(server_socket, 1);

    if(listen_result == FAILURE) {
        close(server_socket);
        std::cout << "<SERVER> Failure to execute the listen functionality...\n";
        return;
    }

    int client_socket = accept(server_socket, (struct sockaddr*) &server_socket_address, (socklen_t*)&server_socket_address);

    if(client_socket == FAILURE) {
        close(server_socket);
        close(client_socket);
        return;
    }

    ssize_t read_result = read(client_socket, buffer, buf_size);

    std::cout << buffer << std::endl;

}
