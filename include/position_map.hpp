#pragma once
#include <unordered_map>
#include <cstdlib>

class PositionMap {
public:
    std::unordered_map<int, int> pos_map; // block_id → leaf index
    int max_leaf;

    PositionMap(int num_leaves);
    int getLeaf(int block_id);
    void assignNewLeaf(int block_id);
};
