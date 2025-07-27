#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>

struct Block {
    int id;             // Block ID
    std::string data;   // Simple payload

    Block(int id = -1, const std::string& data = "")
        : id(id), data(data) {}

    bool isDummy() const {
        return id == -1;
    }
};

#endif
