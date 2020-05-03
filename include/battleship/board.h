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
  Board(size_t tilesize, int row);

  Location LocationOnBoard(Location& loc);

  size_t BoardSize();
};

} // namespace battleship


#endif  // FINALPROJECT_BOARD_H
