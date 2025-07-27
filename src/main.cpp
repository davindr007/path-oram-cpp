#include <iostream>
#include "oram_tree.hpp"

int main() {
    int height = 4; // Height of the ORAM tree
    int Z = 4;      // Blocks per bucket

    ORAMTree tree(height, Z);

    // Write some values
    std::cout << "Writing blocks...\n";
    tree.access("WRITE", 1, "Alice");
    tree.access("WRITE", 2, "Bob");
    tree.access("WRITE", 3, "Charlie");
    tree.access("WRITE", 4, "David");

    // Read them back
    std::cout << "\nReading blocks...\n";
    std::cout << "Block 1: " << tree.access("READ", 1, "").data << "\n";
    std::cout << "Block 2: " << tree.access("READ", 2, "").data << "\n";
    std::cout << "Block 3: " << tree.access("READ", 3, "").data << "\n";
    std::cout << "Block 4: " << tree.access("READ", 4, "").data << "\n";

    // Overwrite
    std::cout << "\nOverwriting Block 2...\n";
    tree.access("WRITE", 2, "BobUpdated");

    // Read again
    std::cout << "\nReading updated Block 2...\n";
    std::cout << "Block 2: " << tree.access("READ", 2, "").data << "\n";

    return 0;
}
