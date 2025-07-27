#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include "oram_tree.hpp"
#include <string>

class Accessor {
private:
    ORAMTree* tree;

public:
    Accessor(ORAMTree* tree);
    void performAccess(const std::string& id, const std::string& data, const std::string& op);
};

#endif
