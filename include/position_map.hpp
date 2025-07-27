#include <unordered_map>
#include <random>

class PositionMap {
private:
    std::unordered_map<int, int> pos_map;
    int num_leaves;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
    PositionMap(int num_blocks, int num_leaves);

    int getLeaf(int block_id);
    void setLeaf(int block_id, int leaf);
    int getRandomLeaf();
};

