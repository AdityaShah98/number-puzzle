# CS 104 Project: Number Puzzle & Number Puzzle Solver
- **Name**: Adi Shah
- **Email**: shahaa@usc.edu
- **Description**:
Order the puzzle from 0 (blank) to 8 left-to-right top-to-bottom by moving tiles in and out of the blank space.
Puzzle board of chosen size created by starting with a solved puzzle and completing chosen number of moves (scrambling). Seed values accepted; boards created with the same seed and the same number of scrambling moves will be identical. Puzzle solving algorithm ("-1 to cheat") uses one of three heuristics: BFS, tiles-out-of-place, or Manhattan distance.
	
- **Usage**: ./puzzle \*size\* \*number of scrambling moves\* \*seed\* \*heuristic number\*
	* input 0 for forced breadth-first search
	* input 1 for priority based on tiles-out-of-place
	* input 2 for priority based on Manhattan heuristic (fastest).
