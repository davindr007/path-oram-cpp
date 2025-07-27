// server.cpp
#include "oram_tree.hpp"
#include "position_map.hpp"
#include "stash.hpp"
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 8192

ORAMTree* global_tree = nullptr;

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_socket, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) break;

        std::string request(buffer);
        if (request.rfind("READPATH", 0) == 0) {
            // Format: READPATH <leaf>
            int leaf = std::stoi(request.substr(9));
            std::vector<Block> path = global_tree->read_path(leaf);

            std::string response;
            for (auto& block : path) {
                response += std::to_string(block.id) + "," + block.data + ";";
            }
            send(client_socket, response.c_str(), response.length(), 0);
        }
        else if (request.rfind("WRITEPATH", 0) == 0) {
            // Format: WRITEPATH <leaf>|id1:data1;id2:data2;...;
            size_t sep = request.find("|");
            int leaf = std::stoi(request.substr(10, sep - 10));
            std::string data = request.substr(sep + 1);

            std::vector<Block> new_path;
            size_t start = 0;
            while ((sep = data.find(";", start)) != std::string::npos) {
                std::string pair = data.substr(start, sep - start);
                if (pair.empty()) break;
                size_t colon = pair.find(":");
                int id = std::stoi(pair.substr(0, colon));
                std::string content = pair.substr(colon + 1);
                new_path.push_back(Block(id, content));
                start = sep + 1;
            }

            global_tree->write_path(leaf, new_path);
            std::string ack = "WRITE_OK";
            send(client_socket, ack.c_str(), ack.length(), 0);
        }
        else {
            std::string err = "INVALID_COMMAND";
            send(client_socket, err.c_str(), err.length(), 0);
        }
    }
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    // Initialize ORAM Tree
    global_tree = new ORAMTree(/* initialize as per your setup */);

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        std::cout << "Client connected." << std::endl;
        handle_client(client_socket);
    }

    delete global_tree;
    return 0;
}
