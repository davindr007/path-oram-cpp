#include "oram_tree.hpp"
#include "position_map.hpp"
#include "stash.hpp"
#include "accessor.hpp"
#include <iostream>
#include <ctime>

int main() {
    srand(time(0)); // Random seed for leaf assignment

    int height = 3; // Tree height (3 → 8 leaves)
    int Z = 4;      // Blocks per bucket

    ORAMTree tree(height, Z);
    PositionMap pos_map(tree.getLeafNodeCount());

    // ✅ Assign random leaves to 3 blocks
    for (int i = 1; i <= 3; ++i) {
        pos_map.assignNewLeaf(i);
        std::cout << "[SETUP] Assigned Block " << i << " → Leaf " << pos_map.getLeaf(i) << "\n";
    }

    std::cout << "[DEBUG] Tree has " << tree.tree.size() << " nodes\n";

    Accessor oram(tree, pos_map);

    // === WRITE Operations ===
    std::cout << "\n[WRITE BLOCKS]\n";

    std::string result;
    result = oram.access(1, WRITE, "A");
    std::cout << "Write Block 1 → A: " << result << "\n";

    result = oram.access(2, WRITE, "B");
    std::cout << "Write Block 2 → B: " << result << "\n";

    result = oram.access(3, WRITE, "C");
    std::cout << "Write Block 3 → C: " << result << "\n";

    // === READ Operations ===
    std::cout << "\n[READ BLOCKS]\n";

    result = oram.access(1, READ);
    std::cout << "Read Block 1: " << result << "\n";

    result = oram.access(2, READ);
    std::cout << "Read Block 2: " << result << "\n";

    result = oram.access(3, READ);
    std::cout << "Read Block 3: " << result << "\n";

    // === Print final path to block 1's current leaf ===
    int leaf = pos_map.getLeaf(1);
    std::cout << "\n[PRINT PATH to Leaf " << leaf << "]\n";
    tree.printPath(leaf);

    return 0;
}
