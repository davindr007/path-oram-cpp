#include "position_map.hpp"
#include <cstdlib>  // For rand()

PositionMap::PositionMap(int num_blocks, int num_leaves) 
    : num_blocks(num_blocks), num_leaves(num_leaves) {
    map.resize(num_blocks);
    for (int i = 0; i < num_blocks; ++i) {
        map[i] = rand() % num_leaves;
    }
}

int PositionMap::get_position(int block_id) const {
    if (block_id < 0 || block_id >= num_blocks) {
        throw std::out_of_range("Invalid block ID in get_position");
    }
    return map[block_id];
}

void PositionMap::set_position(int block_id, int leaf) {
    if (block_id < 0 || block_id >= num_blocks) {
        throw std::out_of_range("Invalid block ID in set_position");
    }
    map[block_id] = leaf;
}
