#pragma once
#include "block.hpp"
#include <vector>
#include <optional>

class Stash {
private:
    std::vector<Block> buffer;

public:
    void addBlock(const Block& block);
    std::optional<Block> getBlock(int id);
    void removeBlock(int id);
    std::vector<Block> getAllBlocks() const;

    void print() const;
};

