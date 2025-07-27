#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include "block.hpp"

class Accessor {
private:
    int leaf;
    Block block;
    BlockOp op;

public:
    Accessor(int leaf, const Block &block, BlockOp op);
    
    int getLeaf() const;
    Block getBlock() const;
    BlockOp getOp() const;
};

#endif // ACCESSOR_HPP
