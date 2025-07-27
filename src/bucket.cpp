#include "bucket.hpp"

Bucket::Bucket(int Z) {
    for (int i = 0; i < Z; ++i) {
        blocks.emplace_back();
    }
}

bool Bucket::addBlock(const Block &block) {
    for (auto &b : blocks) {
        if (b.isDummy) {
            b = block;
            return true;
        }
    }
    return false;
}

Block Bucket::getBlock(int id) const {
    for (const auto &b : blocks) {
        if (!b.isDummy && b.id == id) {
            return b;
        }
    }
    return Block();  // return dummy if not found
}

void Bucket::clear() {
    for (auto &b : blocks) {
        b = Block();  // reset to dummy
    }
}

std::vector<Block> Bucket::getAllBlocks() const {
    return blocks;
}
