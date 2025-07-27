#ifndef POSITION_MAP_HPP
#define POSITION_MAP_HPP
#include <map>
#include <random>
class PositionMap {
    std::map<int, int> map;
    std::mt19937 rng;
public:
    PositionMap() { rng.seed(std::random_device()()); }
    int get_leaf(int id) {
        if (!map.count(id)) map[id] = rng();
        return map[id];
    }
    void update(int id, int leaf) { map[id] = leaf; }
};
#endif
