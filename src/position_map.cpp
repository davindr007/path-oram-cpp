#include "position_map.hpp"

PositionMap::PositionMap(int num_leaves) : max_leaf(num_leaves - 1) {}

int PositionMap::getLeaf(int block_id) {
    if (pos_map.find(block_id) != pos_map.end()) {
    return pos_map[block_id];
    }
    else {
    return -1; // Or handle error
    }
}

void PositionMap::assignNewLeaf(int block_id) {
    int random_leaf = rand() % (max_leaf + 1);
    pos_map[block_id] = random_leaf;
}
