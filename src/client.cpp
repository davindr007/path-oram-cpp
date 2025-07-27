#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define SERVER_ADDR "127.0.0.1"
#define BUFFER_SIZE 4096

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  ./client read <block_id>\n";
    std::cout << "  ./client write <block_id> <data>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    int block_id = std::stoi(argv[2]);
    std::string data = (command == "write" && argc == 4) ? argv[3] : "";

    if (command != "read" && command != "write") {
        printUsage();
        return 1;
    }

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    // Connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock);
        return 1;
    }

    // Format message
    std::string message;
    if (command == "read") {
        message = "READ " + std::to_string(block_id);
    } else {
        message = "WRITE " + std::to_string(block_id) + " " + data;
    }

    // Send request
    send(sock, message.c_str(), message.length(), 0);

    // Receive response
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "Response: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to receive response from server." << std::endl;
    }

    close(sock);
    return 0;
}
