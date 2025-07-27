#include "stash.hpp"
#include <algorithm> // for std::find_if

void Stash::add_block(const Block& block) {
    blocks.push_back(block);
}

Block Stash::get_block(int block_id, bool& found) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->id == block_id) {
            Block result = *it;
            blocks.erase(it);
            found = true;
            return result;
        }
    }
    found = false;
    return Block(); // Return dummy block if not found
}

std::vector<Block> Stash::get_all_blocks() const {
    return blocks;
}

void Stash::set_blocks(const std::vector<Block>& new_blocks) {
    blocks = new_blocks;
}

void Stash::clear() {
    blocks.clear();
}
