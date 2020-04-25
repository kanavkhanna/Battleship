//
// Created by Kanav Khanna on 4/25/20.
//

#include "battleship.h"

namespace battleship {

Battleship::Battleship() : shipBody_{}, is_destroyed_{false} {}

size_t Battleship::Size() const {return shipBody_.size();}

std::deque<Segment>::const_iterator Battleship::cbegin() const {return shipBody_.cbegin();}

std::deque<Segment>::const_iterator Battleship::cend() const { return shipBody_.cend();}

std::deque<Segment>::iterator Battleship::begin() { return shipBody_.begin();}

std::deque<Segment>::iterator Battleship::end() { return shipBody_.end();}

Segment Battleship::Head() const { return shipBody_.front();}

Segment Battleship::Tail() const { return shipBody_.back();}

bool Battleship::IsDestroyed() const {return is_destroyed_;}

void Battleship::DestroyPart(const Segment& shipPart) {
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