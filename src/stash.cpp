#include "stash.hpp"
#include <iostream>

void Stash::addBlock(const Block& block) {
    buffer.push_back(block);
}

std::optional<Block> Stash::getBlock(int id) {
    for (const auto& b : buffer) {
        if (!b.is_dummy && b.id == id)
            return b;
    }
    return std::nullopt;
}

void Stash::removeBlock(int id) {
    buffer.erase(
        std::remove_if(buffer.begin(), buffer.end(),
                       [id](const Block& b) { return !b.is_dummy && b.id == id; }),
        buffer.end()
    );
}

std::vector<Block> Stash::getAllBlocks() const {
    return buffer;
}

void Stash::print() const {
    std::cout << "Stash: ";
    for (const auto& b : buffer) {
        std::cout << (b.is_dummy ? "[dummy]" : "[ID: " + std::to_string(b.id) + "]") << " ";
    }
    std::cout << "\n";
}
int Stash::getSize() const {
    return buffer.size();
}

