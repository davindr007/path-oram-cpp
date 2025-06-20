#pragma once
#include <string>

struct Block {
    int id;
    std::string data;
    bool is_dummy;

    Block(int id = -1, std::string d = "", bool dummy = true)
        : id(id), data(d), is_dummy(dummy) {}
};
