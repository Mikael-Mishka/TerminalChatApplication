#include "client.hpp"

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

void Client::run_client() {

    const char* SERVER_IP_ADRESS = "127.0.0.1";
    const int SERVER_PORT = 6969;

    const int FAILURE = -1;

    int buf_size = 1024;

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_socket_address{};

    server_socket_address.sin_port = htons(SERVER_PORT);
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADRESS);

    int connect_result = connect(client_socket, (struct sockaddr*)&server_socket_address, sizeof(server_socket_address));

    if(connect_result == FAILURE) {
        std::cout << "CONNECTION FAILED!";
        close(client_socket);
        return;
    }

    const char* message = "Hello world!";

    ssize_t write_result = write(client_socket, message, buf_size);

    if(write_result == FAILURE) {
        std::cout << "WRITE OPERATION FAILED!";
        close(client_socket);
        return;
    }

    close(client_socket);
}
