#ifndef ORAM_TREE_HPP
#define ORAM_TREE_HPP

#include "bucket.hpp"
#include "position_map.hpp"
#include "stash.hpp"
#include <vector>
#include <string>

class ORAMTree {
private:
    int height;
    std::vector<Bucket> tree;
    PositionMap posMap;
    Stash stash;

    int getLeafIndex(int leaf) const;
    std::vector<int> getPathIndices(int leaf) const;

public:
    ORAMTree(int height);

    void access(const std::string& id, const std::string& data, const std::string& op);
    void printPath(int leaf) const;
};

#endif
