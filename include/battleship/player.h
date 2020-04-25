//
// Created by Kanav Khanna on 4/26/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>

namespace battleship {

struct Player {
  Player(const std::string& name, size_t score) : name(name), score(score) {}
  std::string name;
  size_t score;
};

} //namespace battleship

#endif  // FINALPROJECT_PLAYER_H
