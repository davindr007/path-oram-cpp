#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    std::cout << "Connected to server.\n";

    // test write
    std::string write_msg = "WRITE 42 HelloWorld";
    send(sock, write_msg.c_str(), write_msg.size(), 0);
    read(sock, buffer, 1024);
    std::cout << "Write response: " << buffer << std::endl;

    // test read
    std::string read_msg = "READ 42";
    send(sock, read_msg.c_str(), read_msg.size(), 0);
    memset(buffer, 0, sizeof(buffer));
    read(sock, buffer, 1024);
    std::cout << "Read response: " << buffer << std::endl;

    close(sock);
    return 0;
}
