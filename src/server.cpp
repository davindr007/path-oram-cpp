#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sstream>
#include "oram_tree.hpp"
#include "block.hpp"

#define PORT 8080

ORAMTree* global_tree;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Waiting for connection...\n";
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    std::cout << "Client connected.\n";

    // initialize ORAMTree with height 4 and Z=4
    global_tree = new ORAMTree(4, 4);

    char buffer[1024] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(new_socket, buffer, 1024);
        if (valread <= 0) break;

        std::string command(buffer);
        std::istringstream iss(command);
        std::string op;
        int blockID;
        std::string data;

        iss >> op >> blockID;
        std::getline(iss, data);
        data = data.substr(1);

        if (op == "READ") {
            Block b = global_tree->access(Operation::READ, blockID, {});
            std::string response = "DATA " + b.data;
            send(new_socket, response.c_str(), response.size(), 0);
        } else if (op == "WRITE") {
            Block newBlock(blockID, data);
            global_tree->access(Operation::WRITE, blockID, newBlock);
            std::string response = "OK";
            send(new_socket, response.c_str(), response.size(), 0);
        }
    }

    close(new_socket);
    close(server_fd);
    delete global_tree;
    return 0;
}

