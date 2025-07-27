#include "../include/oram_tree.hpp"
#include <iostream>

ORAMTree::ORAMTree(int depth, int Z) : depth(depth), Z(Z) {
    int numBuckets = (1 << (depth + 1)) - 1;
    tree.resize(numBuckets);
    for (auto& bucket : tree) {
        bucket = Bucket(Z);
    }
}

int ORAMTree::getLeaf(int index) const {
    return positionMap.getPosition(index);
}

void ORAMTree::access(int index, BlockOp op, const Block& inputBlock, Block& outputBlock) {
    int oldLeaf = positionMap.getPosition(index);
    int newLeaf = rand() % (1 << depth);
    positionMap.setPosition(index, newLeaf);

    // 1. Read path
    std::vector<Block> pathBlocks;
    readPath(oldLeaf, pathBlocks);

    // 2. Add to stash
    for (const auto& blk : pathBlocks) {
        if (!blk.isDummy()) stash.addBlock(blk);
    }

    // 3. Access or update block in stash
    if (op == BlockOp::READ) {
        outputBlock = stash.getBlock(index);
    } else if (op == BlockOp::WRITE) {
        stash.updateBlock(inputBlock);
    }

    // 4. Write path back
    std::vector<Block> evictedBlocks;
    stash.evictToPath(newLeaf, depth, Z, evictedBlocks);
    writePath(oldLeaf, evictedBlocks);
}

void ORAMTree::readPath(int leaf, std::vector<Block>& blocks) {
    int idx = 0;
    for (int level = 0; level <= depth; ++level) {
        Bucket& bucket = tree[idx];
        const std::vector<Block>& bBlocks = bucket.getBlocks();
        blocks.insert(blocks.end(), bBlocks.begin(), bBlocks.end());

        if (leaf & (1 << (depth - level - 1))) idx = 2 * idx + 2;
        else idx = 2 * idx + 1;
    }
}

void ORAMTree::writePath(int leaf, const std::vector<Block>& blocks) {
    int idx = 0;
    int blockIdx = 0;
    for (int level = 0; level <= depth; ++level) {
        Bucket& bucket = tree[idx];
        bucket.clear();
        for (int i = 0; i < Z && blockIdx < blocks.size(); ++i) {
            bucket.addBlock(blocks[blockIdx++]);
        }

        if (leaf & (1 << (depth - level - 1))) idx = 2 * idx + 2;
        else idx = 2 * idx + 1;
    }
}
