CXX=g++
CXXFLAGS=-g -Wall 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=board.o heap.h puzzle_heur.o puzzle_move.o puzzle_solver.o puzzle.o
all: puzzle

puzzle: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

puzzle.o: puzzle.cpp board.h puzzle_heur.h puzzle_solver.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o  puzzle.o -c puzzle.cpp

board.o: board.cpp board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o  board.o -c board.cpp

#heap: heap.h
#	$(CXX) $(CXXFLAGS) $(DEFS) -o heap.o -c

puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o puzzle_heur.o -c puzzle_heur.cpp

puzzle_move.o: puzzle_move.cpp puzzle_move.h board.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o puzzle_move.o -c puzzle_move.cpp

puzzle_solver.o: board.h puzzle_solver.cpp puzzle_solver.h puzzle_move.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o puzzle_solver.o -c puzzle_solver.cpp

clean:
	rm -f *.o puzzle
