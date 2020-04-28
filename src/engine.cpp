//
// Created by Kanav Khanna on 4/26/20.
//

#include "battleship/engine.h"
battleship::Engine::Engine(size_t width, size_t height, size_t tile_size)
    : Engine{width, height,tile_size, static_cast<unsigned>(std::rand())} {
}

battleship::Engine::Engine(size_t width, size_t height,size_t tile_size, unsigned int seed)
    : width_{width}, height_{height}, tile_size_{tile_size}, rng_{seed}, uniform_{0, 1}, gameBoard_{30,27} {
}

void battleship::Engine::Reset() {
  battleships_.clear();
}

void battleship::Engine::Attack(battleship::Location location,
                                const vector<Ship>& opponentBattleships) {
  for (Ship ship : opponentBattleships) {
    for (Segment part : ship.GetShip()) {
      if (part.GetLocation() == location) {
        part.SetVisibility(false);
      }
    }
  }
  attackLocations_.push_back(location);
}

auto battleship::Engine::GetShip(battleship::Location location) -> battleship::Ship {
  for (Ship ship : battleships_) {
    for (Segment part : ship.GetShip()) {
      if (part.GetLocation() == location) {
        return ship;
      }
    }
  }
  return Ship();
}

auto battleship::Engine::GetAttackedLocations() -> vector<battleship::Location> {
  return attackLocations_;
}

auto battleship::Engine::IsAttacked(battleship::Location location) -> bool {
  for (Location loc : attackLocations_) {
    if (loc == location) {
      return true;
    }
  }
  return false;
}

auto battleship::Engine::IsGameOver() -> bool {
  for (const Ship& ship : battleships_) {
    if (!ship.IsDestroyed()) {
      return false;
    }
  }
  return true;
}


void battleship::Engine::PlayGame() {
}

auto battleship::Engine::IsShipMapCreated() -> bool { return isShipMapCreated_; }

void battleship::Engine::SetShipMapCreated(bool value) {isShipMapCreated_ = value;}

void battleship::Engine::AddShip(battleship::Location location, battleship::Direction direction) {
  battleships_.emplace_back(Ship(5,location, direction));
}

void battleship::Engine::DrawShips() {
  cinder::gl::color(cinder::Color(1,0,0));
  /*for (battleship::Location& location : locations_) {
    battleship::Location loc = gameBoard_.LocationOnBoard(location);
    loc = loc.GetCenter();
    cinder::gl::drawSolidCircle({loc.Row(),loc.Col()}, 10);
  }*/

  for (battleship::Ship& ship : battleships_) {
    for (battleship::Location& location : ship.ShipLocation()) {
      battleship::Location loc = gameBoard_.LocationOnBoard(location);
      loc = loc.GetCenter();
      cinder::gl::drawSolidCircle({loc.Row(), loc.Col()}, 10);
    }
  }
}

void battleship::Engine::DrawMap() {
  for (int i = 0; i < gameBoard_.BoardSize(); i++) {
    for (int j = 0; j < gameBoard_.BoardSize(); j++) {
      cinder::gl::color(cinder::Color::white());
      battleship::Location loc = battleship::Location(i,j);
      loc = loc.GetCenter();
      cinder::gl::drawLine({tile_size_*i,tile_size_*j}, {(i)*tile_size_,(j+1)*tile_size_});
      cinder::gl::drawLine({tile_size_*i,tile_size_*j}, {(i+1)*tile_size_,(j)*tile_size_});
      cinder::gl::drawSolidRect(cinder::Rectf((loc.Row()-5),
                                      (loc.Col()-5),
                                      (loc.Row()-5) +10,
                                      (loc.Col()-5) + 10));
    }
  }
}