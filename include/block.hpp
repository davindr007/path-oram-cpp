#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <vector>
struct Block {
    int id = -1; // -1 for dummy blocks
    std::vector<int> data;
    int leaf = 0;
};
#endif
