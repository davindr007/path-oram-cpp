# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and header files
SRC = $(SRC_DIR)/accessor.cpp \
      $(SRC_DIR)/bucket.cpp \
      $(SRC_DIR)/oram_tree.cpp \
      $(SRC_DIR)/position_map.cpp \
      $(SRC_DIR)/stash.cpp

HDR = include/accessor.hpp \
      include/block.hpp \
      include/bucket.hpp \
      include/oram_tree.hpp \
      include/position_map.hpp \
      include/stash.hpp

# Executables
all: local client server

local: $(SRC_DIR)/main.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/local $(SRC_DIR)/main.cpp $(SRC)

client: $(SRC_DIR)/client.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/client $(SRC_DIR)/client.cpp $(SRC)

server: $(SRC_DIR)/server.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/server $(SRC_DIR)/server.cpp $(SRC)

clean:
	rm -f $(BUILD_DIR)/local $(BUILD_DIR)/client $(BUILD_DIR)/server
