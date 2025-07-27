#pragma once

#include "block.hpp"
#include <vector>
#include <algorithm>

class Stash {
private:
    std::vector<Block> blocks;

public:
    void addBlock(const Block& block) {
        blocks.push_back(block);
    }

    bool contains(int block_id) {
        for (const auto& block : blocks) {
            if (block.id == block_id) {
                return true;
            }
        }
        return false;
    }

    Block getBlock(int block_id) {
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->id == block_id) {
                Block found = *it;
                blocks.erase(it);
                return found;
            }
        }
        return Block(-1, "");  // Not found
    }

    std::vector<Block> getAllBlocks() {
        return blocks;
    }

    void setBlocks(const std::vector<Block>& new_blocks) {
        blocks = new_blocks;
    }

    void clear() {
        blocks.clear();
    }
};

