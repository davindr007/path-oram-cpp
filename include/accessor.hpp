#pragma once

#include "oram_tree.hpp"
#include "position_map.hpp"
#include "stash.hpp"
#include <string>

enum BlockOp { READ, WRITE };

class Accessor {
private:
    ORAMTree& tree;
    PositionMap& pos_map;
    Stash stash;

public:
    Accessor(ORAMTree& t, PositionMap& p) : tree(t), pos_map(p) {}

    std::string access(int block_id, AccessType type, const std::string& new_data = "");
};
