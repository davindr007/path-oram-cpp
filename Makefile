CXX = g++
CXXFLAGS = -std=c++11 -O3

all: client server

client: client.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

server: server.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f client server
