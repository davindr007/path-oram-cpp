# ==== Compiler and Flags ====
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# ==== Source Files ====
SRCS = main.cpp accessor.cpp oram_tree.cpp position_map.cpp stash.cpp bucket.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = pathoram

# ==== Default Target ====
all: $(TARGET)

# ==== Link Object Files into Executable ====
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ==== Compile Each .cpp to .o ====
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==== Run Program ====
run: all
	./$(TARGET) --demo=true

# ==== Clean Build Files ====
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run

