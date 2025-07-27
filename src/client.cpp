#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    while (true) {
        std::string command;
        std::cout << "Enter command (read <id> / write <id> <data> / exit): ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        // Send command to server
        send(sock, command.c_str(), command.size(), 0);

        // Read response
        char buffer[BUFFER_SIZE] = {0};
        int valread = read(sock, buffer, BUFFER_SIZE - 1);
        if (valread <= 0) {
            std::cerr << "Server disconnected or error.\n";
            break;
        }

        std::cout << "Server response: " << buffer << "\n";
    }

    close(sock);
    return 0;
}
