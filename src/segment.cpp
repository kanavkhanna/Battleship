//
// Created by Kanav Khanna on 4/25/20.
//

#include "battleship/segment.h"

namespace battleship {
Segment::Segment(Location location)
    : location_(location), visible_{true} {}

Location Segment::GetLocation() const { return location_; }

Location Segment::SetLocation(const battleship::Location& location) {
  location_ = location;
  return location_;
}

void Segment::SetVisibility(bool visible) { visible_ = visible; }

bool Segment::IsVisibile() const { return visible_; }

}