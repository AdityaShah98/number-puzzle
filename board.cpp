#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{ //creates board to specifications by starting with a complete board of
  //specified size and completing specified number of moves to "scramble."
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed); //allows for seeding
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}


Board::Board(const Board &obj){ //copy constructor
  size_ = obj.size_;
  tiles_ = new int[size_];
  for (int i = 0; i < size_; i++){
    tiles_[i] = obj[i];
  }
}

Board& Board::operator=(const Board &rhs)
{ // assignment operator (unused)

  tiles_ = new int[size_];
  *tiles_ = *rhs.tiles_;
  size_ = rhs.size_;

  return *this;
}

Board::~Board(){
  delete [] tiles_;
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> potentialMoves;
  int bc, br, tc, tr;
  int side_dim = dim();
  
  //find blank tile
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  //test if top, bottom, left, and right tiles exist to move
  if (br+1 < side_dim){ //if the tile below blank is valid
    tr = br+1;
    tc = bc;
    Board *temp = new Board(*this);
    temp -> move(tiles_[(tr*side_dim) + tc]);
    potentialMoves[tiles_[(tr*side_dim) + tc]] = temp;
  }
  if (br-1 >= 0){ //if the tile above blank is valid
    tr = br-1;
    tc = bc;
    Board *temp = new Board(*this);
    temp -> move(tiles_[(tr*side_dim) + tc]);
    potentialMoves[tiles_[(tr*side_dim) + tc]] = temp;
  }
  if (bc+1 < side_dim){ //if the tile to the right of blank is valid
    tr = br;
    tc = bc+1;
    Board *temp = new Board(*this);
    temp -> move(tiles_[(tr*side_dim) + tc]);
    potentialMoves[tiles_[(tr*side_dim) + tc]] = temp;
  }
  if (bc-1 >= 0){ //if the tile to the left of blank is valid
    tr = br;
    tc = bc-1;
    Board *temp = new Board(*this);
    temp -> move(tiles_[(tr*side_dim) + tc]);
    potentialMoves[tiles_[(tr*side_dim) + tc]] = temp;
  }
  return potentialMoves;
}

const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

bool Board::operator<(const Board& rhs) const
{
  for (int i = 0; i < size_; i++){ //steps through tile array
    if (tiles_[i] < rhs[i]){ //if current object's tile is less than rhs's
      return true; //return true
    }else if(tiles_[i] > rhs[i]){ //if it's greater, return false
      return false;
    }
  }
  return false;
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}


std::ostream& operator<<(std::ostream &os, const Board &b){
  //print board with correct syntax
  for (int i = 0; i < b.dim(); i++){
    os << endl;
    b.printRowBanner(os); //print row banner before every row
    os << '|';
    for (int j = 0; j < b.dim(); j++){
      if (b[i*b.dim() + j] != 0){
        //sets 2 spaces per tile
        os << setfill(' ') << setw(2) << b[i*b.dim() + j] << '|';
      }else{
        os << "  " << '|';
      }
    }
  }
  os << endl;
  b.printRowBanner(os); //print final row banner
  return os;
}

// Returns true if the board is solved, false otherwise
bool Board::solved() const{
  for (int i = 0; i < (size_ - 1); i++){
    if (tiles_[i] > tiles_[i+1])
      return false;
  }
  return true;
}