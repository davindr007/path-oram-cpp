#include "oram_tree.hpp"
#include "position_map.hpp"
#include "accessor.hpp"
#include "cxxopts.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    std::srand(std::time(nullptr)); // Seed random

    // === CLI PARSER ===
    cxxopts::Options options("PathORAM", "Oblivious RAM with configurable parameters");
    options.add_options()
        ("height", "Tree height", cxxopts::value<int>()->default_value("3"))
        ("Z", "Blocks per bucket", cxxopts::value<int>()->default_value("4"))
        ("blocks", "Number of blocks", cxxopts::value<int>()->default_value("3"))
        ("ops", "Operations (only if blocks > 3)", cxxopts::value<int>()->default_value("10"))
        ("demo", "Run fixed 3-block example", cxxopts::value<bool>()->default_value("true"))
        ("help", "Print help");

    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << "\n";
        return 0;
    }

    int height = result["height"].as<int>();
    int Z = result["Z"].as<int>();
    int num_blocks = result["blocks"].as<int>();
    int ops = result["ops"].as<int>();
    bool demo_mode = result["demo"].as<bool>();

    ORAMTree tree(height, Z);
    PositionMap pos_map(tree.getLeafNodeCount());
    Accessor oram(tree, pos_map);

    for (int i = 1; i <= num_blocks; ++i) {
        pos_map.assignNewLeaf(i);
        std::cout << "[SETUP] Assigned Block " << i << " → Leaf " << pos_map.getLeaf(i) << "\n";
    }

    std::cout << "[DEBUG] Tree has " << tree.tree.size() << " nodes\n";

    if (demo_mode || num_blocks == 3) {
        std::cout << "\n[WRITE BLOCKS]\n";
        std::string result;
        result = oram.access(1, WRITE, "A");
        std::cout << "Write Block 1 → A: " << result << "\n";

        result = oram.access(2, WRITE, "B");
        std::cout << "Write Block 2 → B: " << result << "\n";

        result = oram.access(3, WRITE, "C");
        std::cout << "Write Block 3 → C: " << result << "\n";

        std::cout << "\n[READ BLOCKS]\n";
        result = oram.access(1, READ);
        std::cout << "Read Block 1: " << result << "\n";

        result = oram.access(2, READ);
        std::cout << "Read Block 2: " << result << "\n";

        result = oram.access(3, READ);
        std::cout << "Read Block 3: " << result << "\n";

        int leaf = pos_map.getLeaf(1);
        std::cout << "\n[PRINT PATH to Leaf " << leaf << "]\n";
        tree.printPath(leaf);
    } else {
        std::cout << "\n[BENCHMARK MODE]\n";
        int max_stash = 0;
        for (int i = 0; i < ops; ++i) {
            int block_id = std::rand() % num_blocks + 1;
            std::string data = "data_" + std::to_string(i);
            oram.access(block_id, WRITE, data);
            max_stash = std::max(max_stash, oram.getStashSize());

            if (i % 10 == 0)
                std::cout << "[Benchmark] Op " << i << ", Stash Size: " << oram.getStashSize() << "\n";
        }
        std::cout << "[Benchmark] Max Stash Size: " << max_stash << "\n";
    }

    return 0;
}
