#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP
#include "oram_tree.hpp"
class ORAMAccessor {
    ORAMTree oram;
public:
    ORAMAccessor(int levels) : oram(levels) {}
    std::vector<int> read(int id) { return oram.read(id); }
    void write(int id, const std::vector<int>& data) { oram.write(id, data); }
};
#endif
