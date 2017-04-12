#include "puzzle_solver.h"
#include "heap.h"
using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) : b_(b){
	ph_ = ph;
}

PuzzleSolver::~PuzzleSolver(){

}

void PuzzleSolver::run(){
	expansions_ = 0;
	solution_.clear();
	PuzzleMoveScoreComp comp;

	Heap<PuzzleMove*, PuzzleMoveScoreComp> open_list(2, comp);
	PuzzleMoveSet closed_list;
	PuzzleMove* start = new PuzzleMove(&b_);
	start-> g = 0;
	start-> h = ph_->compute(b_);

	open_list.push(start); //push beginning move to heap
	closed_list.insert(start); //push beginning move to final cheat list
	while (open_list.empty() == false){
		PuzzleMove* k = open_list.top();
		open_list.pop();
		Board* board = k->b;
		if (board->solved()){
			while(k->prev != NULL){
				solution_.push_back(k->tileMove);
				k = k->prev;
			}
			break;
		}
		std::map<int, Board*> new_moves = board->potentialMoves();
		std::map<int, Board*>::iterator iter;

		for (iter = new_moves.begin(); iter != new_moves.end(); ++iter){
			PuzzleMove* puzzlemove = new PuzzleMove(iter->first, iter->second, k);
			puzzlemove->g = k->g + 1;
			puzzlemove->h = ph_->compute(*(puzzlemove->b));

			std::set<PuzzleMove*, PuzzleMoveBoardComp>::iterator iter2;
			iter2 = closed_list.find(puzzlemove);
			if(iter2 == closed_list.end()){
				expansions_++;
				open_list.push(puzzlemove);
				closed_list.insert(puzzlemove);
			}else{
				delete puzzlemove;
			}
		}
	}
	std::set<PuzzleMove*, PuzzleMoveBoardComp>::iterator iter2;
	for (iter2 = closed_list.begin(); iter2 != closed_list.end(); ++iter2){
		delete *iter2;
	}

}


std::deque<int> PuzzleSolver::getSolution(){
	return solution_;
}

int PuzzleSolver::getNumExpansions(){
	return expansions_;
}