#ifndef BUCKET_HPP
#define BUCKET_HPP
#include "block.hpp"
#include <vector>
class Bucket {
    std::vector<Block> blocks;
    const int Z = 4; // Fixed bucket size
public:
    bool add(const Block& b) {
        if (blocks.size() >= Z) return false;
        blocks.push_back(b);
        return true;
    }
    std::vector<Block> remove_all() {
        auto temp = blocks;
        blocks.clear();
        return temp;
    }
    bool is_full() const { return blocks.size() >= Z; }
};
#endif
