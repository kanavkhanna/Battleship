//
// Created by Kanav Khanna on 4/26/20.
//

#include "battleship/ships.h"

battleship::Ships::Ships(vector<Ship> battleships) {
  battleships_ = battleships;
}

battleship::Ship battleship::Ships::GetShip(battleship::Location location) {
  for (Ship ship : battleships_) {
    for (Segment part : ship.GetShip()) {
      if (part.GetLocation() == location) {
        return ship;
      }
    }
  }
  return Ship();
}

void battleship::Ships::Attack(battleship::Location location,
                               vector<Ship> opponentBattleships) {
    for (Ship ship : opponentBattleships) {
        for (Segment part : ship.GetShip()) {
            if (part.GetLocation() == location) {
              part.SetVisibility(false);
            }
        }
    }
    attackLocations_.push_back(location);
}

vector<battleship::Location> battleship::Ships::GetAttackedLocations() {
  return attackLocations_;
}

bool battleship::Ships::IsGameOver() {
  for (Ship ship : battleships_) {
    if (!ship.IsDestroyed())
      return false;
  }
  return true;
}
void battleship::Ships::Reset() {
  battleships_.clear();
}
battleship::Ships::Ships() {}

bool battleship::Ships::IsAttacked(battleship::Location location) {
  for (Location loc : attackLocations_) {
    if (loc == location)
      return true;
  }
  return false;
}
void battleship::Ships::SetShipsLocation() {
  for (Ship ship : battleships_) {
    ship = Ship(5, GetShipSetLocation(), GetShipSetDirection());
  }
}
battleship::Location battleship::Ships::GetShipSetLocation() {
  return battleship::Location(0, 0);
}
battleship::Direction battleship::Ships::GetShipSetDirection() {
  return battleship::Direction::kDown;
}
