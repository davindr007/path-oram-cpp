#ifndef ORAM_TREE_HPP
#define ORAM_TREE_HPP
#include "bucket.hpp"
#include "stash.hpp"
#include "position_map.hpp"
#include <vector>
#include <algorithm>

class ORAMTree {
    int levels;
    std::vector<std::vector<Bucket>> tree;
    Stash stash;
    PositionMap pmap;
    
    std::vector<int> get_path(int leaf) const {
        std::vector<int> path;
        for (int l = 0; l < levels; l++)
            path.push_back((leaf >> (levels - l - 1)));
        return path;
    }
    
    void evict_path(int leaf) {
        auto path = get_path(leaf);
        for (int lvl = 0; lvl < levels; lvl++) {
            Bucket& bucket = tree[lvl][path[lvl]];
            for (auto it = stash.begin(); it != stash.end(); ) {
                Block& b = it->second;
                auto b_path = get_path(b.leaf);
                bool in_subtree = true;
                for (int i = 0; i <= lvl; i++)
                    if (b_path[i] != path[i]) { in_subtree = false; break; }
                
                if (in_subtree && !bucket.is_full()) {
                    bucket.add(b);
                    it = stash.remove(b.id);
                } else {
                    ++it;
                }
            }
        }
    }
    
public:
    ORAMTree(int levels) : levels(levels) {
        tree.resize(levels);
        for (int l = 0; l < levels; l++)
            tree[l].resize(1 << l);
    }
    
    std::vector<int> read(int id) {
        int leaf = pmap.get_leaf(id);
        auto path = get_path(leaf);
        
        for (int lvl = 0; lvl < levels; lvl++)
            for (auto& b : tree[lvl][path[lvl]].remove_all())
                stash.add(b);
        
        pmap.update(id, leaf);
        evict_path(leaf);
        return stash.get(id).data;
    }
    
    void write(int id, const std::vector<int>& data) {
        int leaf = pmap.get_leaf(id);
        stash.add({id, data, leaf});
        pmap.update(id, leaf);
        evict_path(leaf);
    }
};
#endif
