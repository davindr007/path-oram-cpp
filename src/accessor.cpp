#include "accessor.hpp"
#include <algorithm>
#include <iostream>
Accessor::Accessor(ORAMTree& t, PositionMap& p) : tree(t), pos_map(p) {}

std::string Accessor::access(int block_id, AccessType type, std::string new_data) {
    std::cout << "[ACCESS] Start: Block " << block_id << ", Type: " << (type == READ ? "READ" : "WRITE") << "\n";

    int old_leaf = pos_map.getLeaf(block_id);
    std::cout << "[ACCESS] Old Leaf: " << old_leaf << "\n";

    auto path = tree.getPathIndexes(old_leaf);
    std::cout << "[ACCESS] Path Indexes: ";
    for (int idx : path) std::cout << idx << " ";
    std::cout << "\n";

    for (int index : path) {
        for (const auto& b : tree.tree[index].blocks) {
            if (!b.is_dummy)
                stash.addBlock(b);
        }
        tree.tree[index] = Bucket(tree.Z);
    }
    std::cout << "[ACCESS] Path loaded into stash\n";

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
    std::cout << "[ACCESS] Block handled in stash: " << result << "\n";

    pos_map.assignNewLeaf(block_id);
    int new_leaf = pos_map.getLeaf(block_id);
    auto new_path = tree.getPathIndexes(new_leaf);

    std::cout << "[ACCESS] New Leaf: " << new_leaf << ", Path: ";
    for (int idx : new_path) std::cout << idx << " ";
    std::cout << "\n";

    auto stash_blocks = stash.getAllBlocks();
    int z = tree.Z;

    for (int idx : new_path) {
        for (size_t i = 0; i < stash_blocks.size(); ++i) {
            if (tree.tree[idx].blocks.size() < static_cast<size_t>(z)) {
                tree.tree[idx].addBlock(stash_blocks[i]);
                stash_blocks.erase(stash_blocks.begin() + i);
                --i;
            }
        }
    }

    std::cout << "[ACCESS] Eviction complete\n";
    return result;
}

