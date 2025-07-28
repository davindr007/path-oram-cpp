CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRC = src/main.cpp src/bucket.cpp src/stash.cpp src/oram_tree.cpp src/accessor.cpp src/position_map.cpp
INC = -Iinclude

TARGET = oram_simulator

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(TARGET)

clean:
	rm -f $(TARGET)
