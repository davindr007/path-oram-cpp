#include "block.hpp"
#include <vector>

class Bucket {
public:
    std::vector<Block> blocks;
    int maxSize;

    Bucket(int z);

    bool insert(const Block& block);
    std::vector<Block> getBlocks() const;
    void clear();
};

