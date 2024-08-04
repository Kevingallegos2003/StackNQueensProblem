CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = NQueens.o

nqueens: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ $^

NQueens.o: NQueens.cpp
		$(CXX) -g $(CXXFLAGS) -c NQueens.cpp

clean: 
	rm -f *.o nqueens