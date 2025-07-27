#include "bucket.hpp"

Bucket::Bucket(int z) {
    for (int i = 0; i < z; ++i) {
        blocks.emplace_back();  // default dummy blocks
    }
}

bool Bucket::insert(const Block& block) {
    for (auto& b : blocks) {
        if (b.is_dummy) {
            b = block;
            return true;
        }
    }
    return false;  // No space to insert
}

std::vector<Block> Bucket::get_blocks() const {
    return blocks;
}

void Bucket::set_blocks(const std::vector<Block>& new_blocks) {
    blocks = new_blocks;
}

void Bucket::clear() {
    for (auto& block : blocks) {
        block = Block();  // reset to dummy
    }
}
