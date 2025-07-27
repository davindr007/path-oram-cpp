#ifndef BUCKET_HPP
#define BUCKET_HPP

#include "block.hpp"
#include <vector>

class Bucket {
public:
    static const int Z = 4;  // Max number of blocks per bucket
    std::vector<Block> blocks;

    Bucket() {
        blocks.resize(Z, Block());  // Fill with dummy blocks
    }

    bool insert(const Block& blk) {
        for (auto& b : blocks) {
            if (b.isDummy()) {
                b = blk;
                return true;
            }
        }
        return false; // No space
    }

    std::vector<Block> getAllBlocks() const {
        return blocks;
    }
};

#endif
