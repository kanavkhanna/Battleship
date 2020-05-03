//
// Created by Kanav Khanna on 4/25/20.
//

#ifndef FINALPROJECT_SHIP_H
#define FINALPROJECT_SHIP_H

#include <cinder/gl/Shader.h>
#include <cinder/gl/gl.h>

#include <deque>

#include "direction.h"
#include "segment.h"

using namespace std;

namespace battleship {

class Ship {
 private:
  vector<Segment> shipBody_;

 public:
  Ship(Location location, battleship::Direction direction);

  Ship();

  //returns size of the ship
  size_t Size() const;

  //returns the whole ship
  std::vector<Segment>& GetShip();

  bool IsDestroyed();

  Segment Tail() const;
  Segment Head() const;

  vector<Location> ShipLocation();

};

}// namespace battleship

#endif  // FINALPROJECT_SHIP_H
