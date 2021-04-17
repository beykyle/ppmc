all:
	clang++-10 -o ppmc -std=c++17 -Wall -O3 src/ppmc.cpp 

clean:
	rm ppmc
