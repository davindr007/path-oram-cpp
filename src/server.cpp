#include "server.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <tree_levels>" << std::endl;
        return 1;
    }
    
    ORAMServer server(std::stoi(argv[1]));
    
    std::string cmd;
    while (std::getline(std::cin, cmd)) {
        server.process_command(cmd);
    }
    
    return 0;
}
