//
// Created by Kanav Khanna on 4/25/20.
//

#include "ship.h"

namespace battleship {

Ship::Ship(int size, Location location, battleship::Direction direction) {
  is_destroyed_ = false;

  for (int i = 0; i < size; i++) {
    switch (direction) {
      case Direction::kUp:
        shipBody_.push_back(battleship::Segment(location - Location(0, i)));
        break;
      case Direction::kDown:
        shipBody_.push_back(battleship::Segment(location + Location(0, i)));
        break;
      case Direction::kLeft:
        shipBody_.push_back(battleship::Segment(location - Location(i,0)));
        break;
      case Direction::kRight:
        shipBody_.push_back(battleship::Segment(location + Location(i,0)));
        break;
    }
  }
}

size_t Ship::Size() const {return shipBody_.size();}

std::deque<Segment>::const_iterator Ship::cbegin() const {return shipBody_.cbegin();}

std::deque<Segment>::const_iterator Ship::cend() const { return shipBody_.cend();}

std::deque<Segment>::iterator Ship::begin() { return shipBody_.begin();}

std::deque<Segment>::iterator Ship::end() { return shipBody_.end();}

Segment Ship::Head() const { return shipBody_.front();}

Segment Ship::Tail() const { return shipBody_.back();}

bool Ship::IsDestroyed() const {return is_destroyed_;}

void Ship::DestroyPart(const Segment& shipPart) {
  for (Segment& part : shipBody_) {
    if (part.GetLocation() == shipPart.GetLocation()) {
      part.SetVisibility(false);
    }
  }

  for (Segment& part : shipBody_) {
    is_destroyed_ = !part.IsVisibile();
  }
}

}