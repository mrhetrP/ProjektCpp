CXX = g++
CXXFLAGS= -g -std=c++17 -Wall -Wpedantic -lncurses -fsanitize=address
SOURCES = $(wildcard *.cpp)

main: $(SOURCES) 
	$(CXX) $^ -o $@ $(CXXFLAGS)

all: main

clean:
	rm main
