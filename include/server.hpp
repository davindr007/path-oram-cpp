#ifndef SERVER_HPP
#define SERVER_HPP
#include "oram_tree.hpp"
#include <sstream>
#include <iostream>

class ORAMServer {
    ORAMTree oram;
public:
    ORAMServer(int levels) : oram(levels) {}
    
    void process_command(const std::string& cmd) {
        std::istringstream iss(cmd);
        std::string op;
        int id;
        iss >> op >> id;
        
        if (op == "READ") {
            auto data = oram.read(id);
            for (int x : data) std::cout << x << " ";
            std::cout << std::endl;
        }
        else if (op == "WRITE") {
            std::vector<int> data;
            int val;
            while (iss >> val) data.push_back(val);
            oram.write(id, data);
            std::cout << "OK" << std::endl;
        }
    }
};
#endif
