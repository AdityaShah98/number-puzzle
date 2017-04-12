#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
//initialize input variables
int dim = atoi(argv[1]);
int size = dim*dim;
int initMoves = atoi(argv[2]);
int seed = atoi(argv[3]);
int heur = atoi(argv[4]);
//creates board
Board puzzle(dim, initMoves, seed);

PuzzleHeuristic* ph;

if(heur == 0){ //selects appropriate puzzle solver heuristic
	ph = new PuzzleBFSHeuristic;
}else if(heur == 1){
	ph = new PuzzleOutOfPlaceHeuristic;
}else if(heur == 2){
	ph = new PuzzleManhattanHeuristic;
}else{
	ph = new PuzzleBFSHeuristic;
}

cout << puzzle << endl; //outputs board

while(true){
	if(puzzle.solved()==true){ //base case
		break;
	}else{
		cin.exceptions(ios_base::failbit);
		int n = 0;
		cout << "Enter tile number to move or -1 for a cheat: ";
		try{
			cin >> n;
		}catch(const ios_base::failure& e){ //exception for invalid num
			cin.clear();
			cin.ignore();
			continue;
		}

		if(n>= 1 && n< size){
			puzzle.move(n); //player's move
			cout << puzzle << endl;
		}else if(n == -1){ //cheat case
			PuzzleSolver puzzlesolver(puzzle, ph);
			puzzlesolver.run(); //run solver to get solution
			std::deque<int> solution = puzzlesolver.getSolution();
			std::deque<int>::reverse_iterator riter;
			cout << "Try this sequence: " << endl; //outputs solution
			for (riter = solution.rbegin(); riter != solution.rend(); ++riter){
				cout << *riter << " ";
			}
			cout << endl; //output number of expansions used by puzzle solver
			int expansions = puzzlesolver.getNumExpansions(); 
			cout << "(Expansions = " << expansions << ")" << endl << endl;
			cout << puzzle << endl; //outputs board after cheat
		}else if(n==0){
			break;
		}
	}
}

delete ph;





  return 0;
}
