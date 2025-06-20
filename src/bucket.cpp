#include "bucket.hpp"
#include <iostream>

Bucket::Bucket(int z) : Z(z) {
    // Fill the bucket with Z dummy blocks
    for (int i = 0; i < Z; ++i)
        blocks.push_back(Block()); // Default is_dummy = true
}

void Bucket::addBlock(const Block& block) {
    // Replace the first dummy block
    for (int i = 0; i < Z; ++i) {
        if (blocks[i].is_dummy) {
            blocks[i] = block;
            return;
        }
    }
    // Bucket is full, block is ignored (can improve later)
}

void Bucket::print() const {
    for (const auto& b : blocks) {
        std::cout << (b.is_dummy ? "[dummy]" : "[ID: " + std::to_string(b.id) + "]") << " ";
    }
    std::cout << "\n";
}

