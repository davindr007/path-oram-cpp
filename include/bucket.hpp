#pragma once
#include "block.hpp"
#include <vector>

class Bucket {
public:
    int Z; // Max number of blocks in a bucket
    std::vector<Block> blocks;

    Bucket(int z = 4); // Constructor

    void addBlock(const Block& block);  // Add block into the bucket
    void print() const;                 // Print bucket contents
};
