#ifndef STASH_HPP
#define STASH_HPP
#include "block.hpp"
#include <unordered_map>
class Stash {
    std::unordered_map<int, Block> blocks;
public:
    void add(const Block& b) { blocks[b.id] = b; }
    Block get(int id) { return blocks.at(id); }
    bool contains(int id) { return blocks.count(id); }
    void remove(int id) { blocks.erase(id); }
    auto begin() { return blocks.begin(); }
    auto end() { return blocks.end(); }
};
#endif
