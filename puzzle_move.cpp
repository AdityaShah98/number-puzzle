#include "puzzle_move.h"

using namespace std;

// Constructor for starting Board (i.e. initial move)
PuzzleMove::PuzzleMove(Board* board){
	prev = NULL;
	b = board;
	tileMove = -1;
	g = 0;
	h = 0;
}

// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent){
	prev = parent;
	b = board;
	tileMove = tile;
	g = 0;
	h = 0;
}

// Destructor
PuzzleMove::~PuzzleMove(){
	if (g != 0){
		delete b;
	}
}