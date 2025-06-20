#include "oram_tree.hpp"
#include "position_map.hpp"
#include <iostream>
#include <ctime>

int main() {
    srand(time(0)); // Seed for random

    int height = 3; // Tree has 3 levels (0–3)
    int Z = 4;      // Each bucket holds 4 blocks

    ORAMTree tree(height, Z);
    PositionMap pos_map(tree.getLeafNodeCount());

    int no_blocks = 10; // no of blocks for random paths

    // Add 10 blocks to random paths
    for (int block_id = 1; block_id <= no_blocks; ++block_id) {
        pos_map.assignNewLeaf(block_id);
        int leaf = pos_map.getLeaf(block_id);
        std::cout << "Block " << block_id << " → Leaf " << leaf << "\n";

        // Insert block into the first bucket on that path
        auto path = tree.getPathIndexes(leaf);
        for (int i : path) {
            tree.tree[i].addBlock(Block(block_id, "data" + std::to_string(block_id), false));
            break; // Just insert in first available bucket (for testing)
        }
    }

    // Test printing a path
    std::cout << "\nPath to Leaf 3:\n";
    tree.printPath(height);

    return 0;
}
