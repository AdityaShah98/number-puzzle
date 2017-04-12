# CS 104 Project: Number Puzzle & Number Puzzle Solver Implementation
- **Name**: Aditya Shah
- **Email**: shahaa@usc.edu
- **Description**:
Order the puzzle form 0 (blank) to 8 left to right, top to bottom, by moving tiles in and out of the blank space.
Puzzle board of chosen size created by starting with a solved puzzle and completing chosen number of moves (scrambling). Seed values accepted; boards created with the same seed and the same initial number of moves will be identical.

Puzzle solving algorithm ("-1 to cheat") uses one of three heuristics:
	-0 for forced breadth-first search
	-1 for priority based on tiles-out-of-place 
	-2 for priority based on Manhattan heuristic (fastest)
	
Usage: ./puzzle *size* *number of initial moves* *seed* *heuristic number*