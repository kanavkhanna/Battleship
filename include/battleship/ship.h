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
  std::deque<Segment> shipBody_;
  bool is_destroyed_;
  cinder::gl::TextureRef texture_;

 public:
  Ship(int size, Location location, battleship::Direction direction);

  Ship();

  //returns size of the ship
  size_t Size() const;

  //returns the whole ship
  std::deque<Segment> GetShip();

  //Destroys a part of the ship
  void DestroyPart(const Segment&);

  bool IsDestroyed() const;

  Segment Tail() const;
  Segment Head() const;

  std::deque<Segment>::iterator begin();
  std::deque<Segment>::iterator end();
  std::deque<Segment>::const_iterator cbegin() const;
  std::deque<Segment>::const_iterator cend() const;

  void Draw();

  vector<Location> ShipLocation();


};

}// namespace battleship

#endif  // FINALPROJECT_SHIP_H
