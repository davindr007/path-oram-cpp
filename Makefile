CXX = g++
CXXFLAGS = -std=c++17 -O2

SRC = accessor.cpp bucket.cpp oram_tree.cpp position_map.cpp stash.cpp
HDR = accessor.hpp block.hpp bucket.hpp oram_tree.hpp position_map.hpp stash.hpp

all: local client server

local_main: main.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o local_main main.cpp $(SRC)

client: client.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o client client.cpp $(SRC)

server: server.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o server server.cpp $(SRC)

clean:
	rm -f local_main client server
