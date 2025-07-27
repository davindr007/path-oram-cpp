#ifndef STASH_HPP
#define STASH_HPP

#include "block.hpp"
#include <vector>
#include <string>

class Stash {
private:
    std::vector<Block> blocks;

public:
    void addBlock(const Block& block) {
        blocks.push_back(block);
    }

    Block getBlock(const std::string& id) {
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->id == id) {
                Block found = *it;
                blocks.erase(it);
                return found;
            }
        }
        return Block{"", ""}; // Return empty block if not found
    }

    std::vector<Block> getAllBlocks() const {
        return blocks;
    }

    void clear() {
        blocks.clear();
    }
};

#endif
