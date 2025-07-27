#ifndef POSITION_MAP_HPP
#define POSITION_MAP_HPP

#include <unordered_map>
#include <string>

class PositionMap {
private:
    std::unordered_map<std::string, int> posMap;

public:
    void setPosition(const std::string& id, int pos) {
        posMap[id] = pos;
    }

    int getPosition(const std::string& id) const {
        auto it = posMap.find(id);
        if (it != posMap.end()) {
            return it->second;
        }
        return -1; // Not found
    }
};

#endif
