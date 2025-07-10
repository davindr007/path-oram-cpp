# ==== Compiler and Flags ====
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# ==== Source Files ====
SRCS = src/main.cpp src/accessor.cpp src/oram_tree.cpp src/stash.cpp src/bucket.cpp src/position_map.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = oram

# ==== Default Target ====
all: $(TARGET)

# ==== Link Object Files ====
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ==== Compile Each .cpp to .o ====
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==== Run Program ====
run: all
	./$(TARGET) --demo=true

# ==== Clean Up ====
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
