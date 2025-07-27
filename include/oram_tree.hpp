#include "bucket.hpp"
#include "block.hpp"
#include <vector>

class ORAMTree {
private:
    int height;
    int Z;
    std::vector<Bucket> tree;

    int getNodeIndex(int level, int index) const;
    std::vector<int> pathToRoot(int leaf) const;

public:
    ORAMTree(int h, int z);

    std::vector<Block> readPath(int leaf) const;
    void writePath(int leaf, const std::vector<Block>& path);
    bool insertBlockAtLeaf(int leaf, const Block& block);
};

