#include "oram_tree.hpp"
#include "position_map.hpp"
#include "stash.hpp"
#include "accessor.hpp"
#include <iostream>
#include <ctime>

int main() {
    srand(time(0)); // Random seed

    int height = 3; // Tree height (3 → 8 leaves)
    int Z = 4;      // Blocks per bucket

    ORAMTree tree(height, Z);
    PositionMap pos_map(tree.getLeafNodeCount());

    // Pre-assign leaf for blocks
    for (int i = 1; i <= 3; ++i)
        pos_map.assignNewLeaf(i);

    Accessor oram(tree, pos_map);

    // WRITE operations
    std::cout << "\n[WRITE BLOCKS]\n";
    std::cout << "Write Block 1 → A: " << oram.access(1, WRITE, "A") << "\n";
    std::cout << "Write Block 2 → B: " << oram.access(2, WRITE, "B") << "\n";
    std::cout << "Write Block 3 → C: " << oram.access(3, WRITE, "C") << "\n";

    // READ operations
    std::cout << "\n[READ BLOCKS]\n";
    std::cout << "Read Block 1: " << oram.access(1, READ) << "\n";
    std::cout << "Read Block 2: " << oram.access(2, READ) << "\n";
    std::cout << "Read Block 3: " << oram.access(3, READ) << "\n";

    // Print tree path for Block 1’s new leaf
    int leaf = pos_map.getLeaf(1);
    std::cout << "\n[PRINT PATH to Leaf " << leaf << "]\n";
    tree.printPath(leaf);

    return 0;
}
