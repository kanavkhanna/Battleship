//
// Created by Kanav Khanna on 4/25/20.
//

#include "battleship/ship.h"
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>

namespace battleship {

Ship::Ship() {}

Ship::Ship(int size, Location location, battleship::Direction direction) {
  texture_ = cinder::gl::Texture2d::create(cinder::loadImage(
      "/Users/kanavkhanna/Downloads"
      "/cinder_0.9.2_mac/my-projects/final-project-kanavk26/assets/ship.jpg" ));

  for (int i = 0; i < size; i++) {
    switch (direction) {
      case Direction::kUp:
        shipBody_.emplace_back((location - Location(0, i*30)));
        break;
      case Direction::kDown:
        shipBody_.emplace_back(location + Location(0, i*30));
        break;
      case Direction::kLeft:
        shipBody_.emplace_back(location - Location(i*30,0));
        break;
      case Direction::kRight:
        shipBody_.emplace_back(location + Location(i*30,0));
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
std::deque<Segment> Ship::GetShip() { return shipBody_; }

vector<Location> Ship::ShipLocation() {
  vector<Location> location;

  for (Segment& part : shipBody_) {
    location.emplace_back(part.GetLocation());
  }
  return location;
}

}  // namespace battleship