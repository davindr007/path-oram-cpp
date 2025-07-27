#include <string>
enum BlockOp { READ, WRITE };
class Block {
public:
    int id;
    std::string data;
    bool isDummy;

    Block(int i = -1, const std::string& d = "", bool dummy = true)
        : id(i), data(d), isDummy(dummy) {}
};

