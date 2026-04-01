CXX := g++
CXXFLAGS := -std=gnu++17 -O2 -pipe -s

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f code *.o
