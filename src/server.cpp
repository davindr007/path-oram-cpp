#include "server.hpp"
int main() {
    ORAMServer server(4); // 4-level tree
    server.run();
}
