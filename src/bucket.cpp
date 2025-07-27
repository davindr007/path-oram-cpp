#include "block.hpp"
#include <sstream>

Block::Block(int id, const std::vector<uint8_t>& data, int leaf_id) 
    : id(id), data(data), leaf_id(leaf_id) {}

bool Block::is_dummy() const { return id == -1; }

size_t Block::size() const { return data.size(); }

std::string Block::to_string() const {
    std::ostringstream oss;
    oss << "Block[id=" << id 
        << ", leaf=" << leaf_id 
        << ", size=" << data.size() 
        << ", data=" << (is_dummy() ? "DUMMY" : "REAL") << "]";
    return oss.str();
}
