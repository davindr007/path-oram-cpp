#pragma once
#include "bucket.hpp"
#include <vector>
#include <cmath>

class ORAMTree {
public:
    std::vector<Bucket> tree;  // Tree stored as flat array of buckets
    int height;                // Height of the tree (excluding root level)
    int Z;                     // Blocks per bucket

    ORAMTree(int h, int z);
    int getLeafNodeCount() const;
    int getNodeIndex(int level, int offset) const;
    std::vector<int> getPathIndexes(int leaf) const;
    void printPath(int leaf) const;
};
