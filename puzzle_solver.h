#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"


class PuzzleSolver
{
 public:
  typedef std::set<PuzzleMove*, PuzzleMoveBoardComp> PuzzleMoveSet;

  // Constructor (makes a copy of the Board and stores it in b_)
  //  Also takes a PuzzleHeuristic which will score boards
  PuzzleSolver(const Board &b, PuzzleHeuristic* ph);

  // Destructor
  ~PuzzleSolver();

  // Run the A* search and builds the solution and tracks
  // the number of expansions
  void run();

  // Return the solution deque
  std::deque<int> getSolution();

  // Return how many expansions were performed in the search
  int getNumExpansions();
 private:
  Board b_;
  std::deque<int> solution_;
  int expansions_;
  PuzzleHeuristic *ph_;
};

#endif
