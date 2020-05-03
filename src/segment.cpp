//
// Created by Kanav Khanna on 4/25/20.
//

#include "battleship/segment.h"

#include <cinder/gl/gl.h>

namespace battleship {
Segment::Segment(Location location)
    : location_(location), visible_{true} {}

Location Segment::GetLocation() { return location_; }

void Segment::SetVisibility(bool visible) { visible_ = visible; }

bool Segment::IsVisibile() const { return visible_; }


}  // namespace battleship