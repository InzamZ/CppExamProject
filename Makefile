sources = *.cpp
CXX =g++
cxxflags = -std=c++20 -Wall -g -fsanitize=address
target = main

all:
	$(CXX)	$(sources)	$(cxxflags)	-o $(target) 

