#include "accessor.hpp"
#include <iostream>
int main() {
    ORAMAccessor oram(4); // 4-level ORAM
    
    // Test sequence
    oram.write(1, {1,2,3});
    oram.write(2, {4,5,6});
    
    auto data = oram.read(1);
    std::cout << "Read data:";
    for (int x : data) std::cout << " " << x;
    std::cout << std::endl;
    
    return 0;
}
