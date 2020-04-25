//
// Created by Kanav Khanna on 4/25/20.
//

#ifndef FINALPROJECT_BATTLESHIP_H
#define FINALPROJECT_BATTLESHIP_H

#include "segment.h"
#include <deque>

using namespace std;

namespace battleship {

class Battleship {
 private:
  std::deque<Segment> shipBody_;
  bool is_destroyed_;

 public:
  Battleship();

  //returns size of the ship
  size_t Size() const;

  //Destroys a part of the ship
  void DestroyPart(const Segment&);

  bool IsDestroyed() const;

  Segment Tail() const;
  Segment Head() const;

  std::deque<Segment>::iterator begin();
  std::deque<Segment>::iterator end();
  std::deque<Segment>::const_iterator cbegin() const;
  std::deque<Segment>::const_iterator cend() const;


};

}// namespace battleship

#endif  // FINALPROJECT_BATTLESHIP_H
