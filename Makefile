CXX := g++-13
CXXFLAGS := -std=gnu++17 -O2 -pipe -static -s

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f code *.o

