#include "accessor.hpp"

Accessor::Accessor(int leaf, const Block &block, BlockOp op)
    : leaf(leaf), block(block), op(op) {}

int Accessor::getLeaf() const {
    return leaf;
}

Block Accessor::getBlock() const {
    return block;
}

BlockOp Accessor::getOp() const {
    return op;
}
