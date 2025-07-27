#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <cstdint>
#include <string>

class Block {
public:
    int id;  // -1 for dummy blocks
    std::vector<uint8_t> data;
    int leaf_id;
    
    Block(int id = -1, const std::vector<uint8_t>& data = {}, int leaf_id = 0);
    bool is_dummy() const;
    size_t size() const;
    std::string to_string() const;  // Debug method
};

#endif
