#include "accessor.hpp"
#include <iostream>

Accessor::Accessor(ORAMTree& t, PositionMap& p) : tree(t), pos_map(p) {}

std::string Accessor::access(int block_id, AccessType type, const std::string& new_data) {
    int old_leaf = pos_map.get_leaf(block_id);
    int new_leaf = tree.get_random_leaf();
    pos_map.set_leaf(block_id, new_leaf);

    std::vector<Block> path = tree.read_path(old_leaf);
    
    // Move blocks from path into stash
    for (const auto& block : path) {
        if (!block.is_dummy) {
            stash.insert(block);
        }
    }

    std::string result_data;

    // Access or update data
    if (stash.contains(block_id)) {
        Block& blk = stash.get(block_id);
        if (type == READ) {
            result_data = blk.data;
        } else if (type == WRITE) {
            blk.data = new_data;
        }
    } else if (type == WRITE) {
        Block new_block(block_id, new_data);
        stash.insert(new_block);
    }

    std::vector<Block> new_path = stash.evict_blocks(tree, old_leaf);
    tree.write_path(old_leaf, new_path);

    return result_data;
}
