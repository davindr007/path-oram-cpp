#pragma once
#include "oram_tree.hpp"
#include "position_map.hpp"
#include "stash.hpp"
#include <string>

enum AccessType { READ, WRITE };

class Accessor {
private:
    ORAMTree& tree;
    PositionMap& pos_map;
    Stash stash;

public:
    Accessor(ORAMTree& t, PositionMap& p);
    std::string access(int block_id, AccessType type, std::string new_data = "");
    int getStashSize() const;
};
