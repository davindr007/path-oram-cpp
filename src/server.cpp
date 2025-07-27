#ifndef SERVER_HPP
#define SERVER_HPP
#include "oram_tree.hpp"
#include <iostream>
class ORAMServer {
    ORAMTree oram;
public:
    ORAMServer(int levels) : oram(levels) {}
    void run() {
        std::string cmd;
        while (std::getline(std::cin, cmd)) {
            std::istringstream iss(cmd);
            std::string op;
            int id;
            iss >> op >> id;
            
            if (op == "READ") {
                auto data = oram.read(id);
                for (int x : data) std::cout << x << " ";
                std::cout << "\n";
            }
            else if (op == "WRITE") {
                std::vector<int> data;
                int x;
                while (iss >> x) data.push_back(x);
                oram.write(id, data);
                std::cout << "OK\n";
            }
        }
    }
};
#endif
