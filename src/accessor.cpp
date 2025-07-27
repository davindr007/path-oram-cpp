#include "../include/accessor.hpp"
#include <iostream>

Accessor::Accessor(ORAMTree* tree, PositionMap* posMap) {
    this->oramTree = tree;
    this->posMap = posMap;
    this->accessCounter = 0;
}

void Accessor::access(int blockId, BlockOp op, const std::string& data) {
    int oldLeaf = posMap->getPosition(blockId);
    int newLeaf = rand() % (1 << oramTree->getHeight());
    posMap->setPosition(blockId, newLeaf);

    std::vector<Block> path = oramTree->readPath(oldLeaf);

    bool found = false;
    for (auto& block : path) {
        if (block.id == blockId) {
            if (op == BlockOp::WRITE) {
                block.data = data;
            } else if (op == BlockOp::READ) {
                std::cout << "Client Read: Block " << blockId << " = " << block.data << std::endl;
            }
            found = true;
            break;
        }
    }

    if (!found && op == BlockOp::WRITE) {
        path.push_back(Block(blockId, data));
    }

    oramTree->writePath(oldLeaf, path);
    accessCounter++;
    std::cout << "Client: Access counter = " << accessCounter << std::endl;
}
