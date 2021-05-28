sources = *.cpp
CXX =g++
cxxflags = -std=c++2a -Wall -g -fsanitize=address
target = main

all:
	$(CXX)	$(sources)	$(cxxflags)	-o $(target) 

