#include "oram_tree.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

ORAMTree::ORAMTree(int h, int z) : height(h), Z(z) {
    num_leaves = 1 << height; // 2^height
    tree.resize((1 << (height + 1)) - 1); // Full binary tree node count
    for (auto &bucket : tree)
        bucket = Bucket(Z);
}

std::vector<Block> ORAMTree::read_path(int leaf) {
    std::vector<Block> path;
    int index = 0;

    for (int level = 0; level <= height; level++) {
        path.push_back(tree[index].get_blocks());
        index = 2 * index + 1 + ((leaf >> (height - level)) & 1);
    }

    return path;
}

void ORAMTree::write_path(int leaf, const std::vector<Block> &path_blocks) {
    int index = 0;
    int block_index = 0;

    for (int level = 0; level <= height; level++) {
        std::vector<Block> new_bucket;
        for (int i = 0; i < Z && block_index < path_blocks.size(); i++, block_index++) {
            new_bucket.push_back(path_blocks[block_index]);
        }
        tree[index].set_blocks(new_bucket);
        index = 2 * index + 1 + ((leaf >> (height - level)) & 1);
    }
}

std::vector<int> ORAMTree::get_path(int leaf) {
    std::vector<int> path;
    int index = 0;

    for (int level = 0; level <= height; level++) {
        path.push_back(index);
        index = 2 * index + 1 + ((leaf >> (height - level)) & 1);
    }

    return path;
}

Block ORAMTree::access(const std::string &op, int id, const std::string &data) {
    int old_leaf = position_map.get_position(id);
    int new_leaf = rand() % num_leaves;
    position_map.set_position(id, new_leaf);

    std::vector<int> path = get_path(old_leaf);
    for (int node : path) {
        std::vector<Block> bucket_blocks = tree[node].get_blocks();
        for (const auto &blk : bucket_blocks) {
            if (!blk.is_dummy)
                stash.add_block(blk);
        }
    }

    Block result;
    if (op == "READ") {
        result = stash.read_block(id);
    } else if (op == "WRITE") {
        Block new_block(id, data);
        stash.write_block(new_block);
        result = new_block;
    }

    // Refill buckets from stash (from bottom to root)
    for (int i = path.size() - 1; i >= 0; i--) {
        std::vector<Block> candidates = stash.get_blocks_on_path(path[i], height, Z);
        tree[path[i]].set_blocks(candidates);
        stash.remove_blocks(candidates);
    }

    return result;
}
