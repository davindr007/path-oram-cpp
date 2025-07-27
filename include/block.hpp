#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <vector>
struct Block {
    int id = -1; // -1 = dummy
    std::vector<int> data;
    int leaf = 0;
};
#endif
