#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

#include "board.h"

class PuzzleHeuristic
{
 public:
  virtual ~PuzzleHeuristic() { }
  virtual int compute(const Board& b) = 0;
};


class PuzzleManhattanHeuristic : public PuzzleHeuristic
{
 public:
  int compute(const Board& b);
};

class PuzzleOutOfPlaceHeuristic : public PuzzleHeuristic
{
 public:
  int compute(const Board& b);
};

class PuzzleBFSHeuristic : public PuzzleHeuristic
{
 public:
  int compute(const Board& b);
};


#endif
