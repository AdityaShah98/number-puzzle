#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>

class Board
{
 public:

  // Init a board of given dimension (size = dim^2) and 
  // scramble it with numInitMoves by moving 
  // the space tile with a randomly chosen direction N, W, S, E
  // some of which may be invalid, in which case we skip that move
  Board(int dim, int numInitMoves, int seed);

  // ****** Add a copy constructor, destructor, etc. if you need them ****** //




  // Swaps the blank with the specified tile value
  void move(int tile);

  // Generate potential moves and fill in the map with 
  // Key=tile, Value=Ptr to corresponding Board
  // Clear the moveMap as the first order of business.
  //void potentialMoves(map<int, Board*> &moveMap); 
  std::map<int, Board*> potentialMoves() const; 

  // Returns true if the board is solved, false otherwise
  bool solved() const;

  //---------- Operators --------------//

  // Prints the board in the desired 2D format (utilizes printRowBanner())
  friend std::ostream& operator<<(std::ostream &os, const Board &b);

  // Checks if this board is less-than another.  We define less than
  // as a "string-style" comparison of the tile array (i.e. Starting by comparing
  // the 0-th tile in this Board and the other.
  // If this board's tile is less than the other board's tile value, return true
  // If they are equal, continue with the next tile location and repeat
  bool operator<(const Board& rhs) const;
  
  //---------- Accessors --------------//

  // Returns the tile value at location, loc
  //  Let's a user treat the board object like an array to get a tile value
  //  at a given index
  int const & operator[](int loc) const;

  // Returns the size of the tiles array
  int size() const;

  // Returns the dimension of the board (i.e. sqrt(size) )
  int dim() const;
  
 private:
  // Prints the row banner at the top, bottom, and in between tile rows
  void printRowBanner(std::ostream& os) const;

  // Do not modify...use these as your data members. No vectors/lists/dequees
  //  we want you to manage memory explicitly for the learning experience.

  int *tiles_; // Will point to an array
  int size_;   // Size of the array
};


#endif
