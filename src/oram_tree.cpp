#include "oram_tree.hpp"
#include <iostream>
#include <algorithm>

ORAMTree::ORAMTree(int h, int z) : height(h), Z(z) {
    int total_nodes = std::pow(2, height + 1) - 1;
    tree = std::vector<Bucket>(total_nodes, Bucket(Z));
}

int ORAMTree::getLeafNodeCount() const {
    return std::pow(2, height);
}

int ORAMTree::getNodeIndex(int level, int offset) const {
    return std::pow(2, level) - 1 + offset;
}

std::vector<int> ORAMTree::getPathIndexes(int leaf) const {
    std::vector<int> path;
    int index = leaf + (1 << height) - 1;
    while (index >= 0) {
        path.push_back(index);
        index = (index - 1) / 2; // Move to parent
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void ORAMTree::printPath(int leaf) const {
    auto path = getPathIndexes(leaf);
    for (int i : path) {
        std::cout << "Bucket " << i << ": ";
        tree[i].print();
    }
}
