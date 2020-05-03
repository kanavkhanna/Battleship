//
// Created by Kanav Khanna on 4/25/20.
//

#include "battleship/ship.h"
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include <random>

namespace battleship {

Ship::Ship() {}

Ship::Ship(Location location, battleship::Direction direction) {
  //setting up random distribution for ship size
  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_real_distribution<> dist(3, 10);
  int ship_size = dist(e2);

  for (int i = 0; i < ship_size; i++) {
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

Segment Ship::Head() const { return shipBody_.front();}

Segment Ship::Tail() const { return shipBody_.back();}


/*void Ship::DestroyPart(const Segment& shipPart) {
  for (Segment& part : shipBody_) {
    if (part.GetLocation() == shipPart.GetLocation()) {
      part.SetVisibility(false);
    }
  }

  for (Segment& part : shipBody_) {
    is_destroyed_ = !part.IsVisibile();
  }
}*/

bool Ship::IsDestroyed() {
  for (Segment& part : shipBody_) {
    if (part.IsVisibile()) {
      return false;
    }
  }
  return true;
}

std::vector<Segment>& Ship::GetShip() { return shipBody_; }

vector<Location> Ship::ShipLocation() {
  vector<Location> location;

  for (Segment& part : shipBody_) {
    location.emplace_back(part.GetLocation());
  }
  return location;
}

}  // namespace battleship