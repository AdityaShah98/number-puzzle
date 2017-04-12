#include "puzzle_heur.h"
#include <cmath>

int PuzzleManhattanHeuristic::compute(const Board& b){
	int val = 0, goalrow, goalcol;
	int row, col;

	for (int i = 0; i < b.size(); i++){ //for all tiles
		if (b[i] != 0){ //as long as it's not the blank tile...
			row = i / b.dim(); //finds row of current tile
			col = i % b.dim(); //finds col of current tile
			goalrow = b[i] / b.dim(); //finds row of current tile's target
			goalcol = b[i] % b.dim(); //finds col of current tile's target

			//adds "manhattan distance" of tile to board's value
			val += std::abs((goalrow - row) + (goalcol - col)); 
		}
	}
	return val;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b){
	int val = 0, goalrow, goalcol;
	int row, col;

	for (int i = 0; i < b.size(); i++){ //for all tiles
		//std::cout<<b.size()<<" ";
		if (b[i] != 0){ //as long as it's not the blank tile...
			row = i / b.dim();
			col = i % b.dim(); //finds col of current tile
			goalrow = b[i] / b.dim(); //finds row of current tile's target
			goalcol = b[i] % b.dim(); //finds col of current tile's target

			if ((row != goalrow) && (col != goalcol))
				val++;
		}
	}
	return val;
}

int PuzzleBFSHeuristic::compute(const Board& b){
	return 0; //return 0
}