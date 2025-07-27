#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <unistd.h>

#include "oram_tree.hpp"
#include "block.hpp"

#define PORT 8080
#define BUFFER_SIZE 4096

ORAMTree* global_tree = nullptr;
std::mutex tree_mutex;

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) break;

        std::string input(buffer);
        std::istringstream iss(input);
        std::string cmd;
        int block_id;
        std::string data;

        iss >> cmd >> block_id;

        if (cmd == "read") {
            std::lock_guard<std::mutex> lock(tree_mutex);
            Block result = global_tree->access("READ", block_id, "");
            std::string response = result.data;
            send(client_socket, response.c_str(), response.size(), 0);
        } 
        else if (cmd == "write") {
            iss >> data;
            std::lock_guard<std::mutex> lock(tree_mutex);
            global_tree->access("WRITE", block_id, data);
            std::string response = "WRITE OK";
            send(client_socket, response.c_str(), response.size(), 0);
        } 
        else {
            std::string response = "Invalid command";
            send(client_socket, response.c_str(), response.size(), 0);
        }
    }

    close(client_socket);
}

int main() {
    int height = 4; // tree height
    int Z = 4;      // blocks per bucket
    global_tree = new ORAMTree(height, Z);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "...\n";

    while (true) {
        socklen_t addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (client_socket < 0) {
            std::cerr << "Failed to accept connection\n";
            continue;
        }

        std::thread t(handle_client, client_socket);
        t.detach(); // detach to allow multiple clients
    }

    delete global_tree;
    return 0;
}
