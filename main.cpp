#include <iostream>

// Network things
#include <netinet/in.h> // AF_INET
#include <sys/socket.h> // Socket
#include <unistd.h> // Read function
#include <arpa/inet.h> // For inet_addr for client

int run_server() {

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
        return EXIT_FAILURE;
    }

    int listen_result = listen(server_socket, 1);

    if(listen_result == FAILURE) {
        close(server_socket);
        std::cout << "<SERVER> Failure to execute the listen functionality...\n";
        return EXIT_FAILURE;
    }

    int client_socket = accept(server_socket, (struct sockaddr*) &server_socket_address, (socklen_t*)&server_socket_address);

    if(client_socket == FAILURE) {
        close(server_socket);
        close(client_socket);
        return EXIT_FAILURE;
    }

    ssize_t read_result = read(client_socket, buffer, buf_size);

    std::cout << buffer << std::endl;

}


int run_client() {

    const char* SERVER_IP_ADRESS = "127.0.0.1";
    const int SERVER_PORT = 6969;

    const int FAILURE = -1;

    int buf_size = 1024;

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_socket_address;

    server_socket_address.sin_port = htons(SERVER_PORT);
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADRESS);

    int connect_result = connect(client_socket, (struct sockaddr*)&server_socket_address, sizeof(server_socket_address));

    if(connect_result == FAILURE) {
        std::cout << "CONNECTION FAILED!";
        close(client_socket);
    }

    const char* message = "Hello world!";

    ssize_t write_result = write(client_socket, message, buf_size);

    if(write_result == FAILURE) {
        std::cout << "WRITE OPERATION FAILED!";
        close(client_socket);
    }

    close(client_socket);
}


int main() {

    std::string user_input;

    std::cout << "[s]/[c]";
    std::cin >> user_input;

    if(user_input == "s") {
        return run_server();
    }

    else if(user_input == "c"){
        return run_client();
    }

    else {
        std::cout << "ERROR: BAD INPUT!";
    }

    return 0;
}


