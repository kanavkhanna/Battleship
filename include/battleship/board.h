//
// Created by Kanav Khanna on 4/28/20.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

#include <cstddef>
#include <vector>
#include <map>
#include "Location.h"

using namespace std;
namespace battleship {


class Board {
 private:
  vector<vector<Location>> boardVec_;
  vector<vector<int>> tileOnBoard_;
  map<int, Location> board_;

 public:
  //constructor for Board
  Board(size_t tilesize, int row);

  //Returns the location of the window in terms of that of the board (i.e in terms of rows and columns)
  Location LocationOnBoard(Location& loc);

  //returns the board size
  size_t BoardSize();
};

} // namespace battleship


#endif  // FINALPROJECT_BOARD_H
