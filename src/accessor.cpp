#include "accessor.hpp"
#include <algorithm>

Accessor::Accessor(ORAMTree& t, PositionMap& p) : tree(t), pos_map(p) {}

std::string Accessor::access(int block_id, AccessType type, std::string new_data) {
    // 1. Get current leaf from position map
    int old_leaf = pos_map.getLeaf(block_id);

    // 2. Get full path indexes
    auto path = tree.getPathIndexes(old_leaf);

    // 3. Move blocks from path into stash
    for (int index : path) {
        for (const auto& b : tree.tree[index].blocks) {
            if (!b.is_dummy)
                stash.addBlock(b);
        }
        tree.tree[index] = Bucket(tree.Z); // Reset bucket (empty with dummies)
    }

    // 4. Read or write in stash
    std::string result = "NOT FOUND";
    auto block_opt = stash.getBlock(block_id);

    if (type == READ) {
        if (block_opt)
            result = block_opt->data;
    } else if (type == WRITE) {
        if (block_opt) stash.removeBlock(block_id);
        stash.addBlock(Block(block_id, new_data, false));
        result = "WRITE DONE";
    }

    // 5. Assign a new leaf for the block
    pos_map.assignNewLeaf(block_id);
    int new_leaf = pos_map.getLeaf(block_id);
    auto new_path = tree.getPathIndexes(new_leaf);

    // 6. Evict blocks from stash back to tree path
    auto stash_blocks = stash.getAllBlocks();
    int z = tree.Z;

    for (int idx : new_path) {
        for (int i = 0; i < stash_blocks.size(); ++i) {
            if (tree.tree[idx].blocks.size() < z) {
                tree.tree[idx].addBlock(stash_blocks[i]);
                stash_blocks.erase(stash_blocks.begin() + i);
                --i;
            }
        }
    }

    return result;
}
