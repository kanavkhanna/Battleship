//
// Created by Kanav Khanna on 4/28/20.
//

#include "battleship/board.h"

namespace battleship {
battleship::Board::Board(size_t tilesize, int row) {
  int tileNo = 1;
  vector<vector<Location>> boardVec(row);
  vector<vector<int>> tileOnBoard(row);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < row; j++) {
      board_.insert(pair<int, Location>(tileNo, Location(i,j)));
      boardVec.at(i).emplace_back(Location(i,j));
      tileOnBoard.at(i).emplace_back(tileNo++);
    }
  }
  boardVec_ = boardVec;
  tileOnBoard_ = tileOnBoard;
}

auto battleship::Board::LocationOnBoard(
    battleship::Location& loc) -> battleship::Location {
  Location location = loc/30;
  return location;
}
size_t Board::BoardSize() { return boardVec_.size()*boardVec_.at(0).size(); }

} //namespace battleship