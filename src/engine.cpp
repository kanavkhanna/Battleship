//
// Created by Kanav Khanna on 4/26/20.
//

#include "battleship/engine.h"

#include <utility>
namespace battleship {
battleship::Engine::Engine(std::string player_name,size_t width, size_t height, size_t tile_size)
    : Engine{std::move(player_name),width, height,tile_size, static_cast<unsigned>(std::rand())} {
}

battleship::Engine::Engine(std::string player_name,size_t width, size_t height,size_t tile_size, unsigned int seed)
    : player_name_{std::move(player_name)},width_{width}, height_{height}, tile_size_{tile_size}, rng_{seed}, uniform_{0, 1}, gameBoard_{30,27} {
}

void battleship::Engine::Reset() {
  battleships_.clear();
}

void battleship::Engine::Attack(battleship::Location location,
                                 vector<Ship>& opponentBattleships) {
  for (Ship& ship : opponentBattleships) {
    for (Segment& part : ship.GetShip()) {
      Location loc = part.GetLocation();
      if (gameBoard_.LocationOnBoard(loc) == gameBoard_.LocationOnBoard(location)) {
        part.SetVisibility(false);
        successfulAttackLocs_.emplace_back(location);
        break;
      }
    }
  }
}

auto battleship::Engine::IsGameOver() -> bool {
  if (battleships_.size() > 0) {
    for (Ship& ship : battleships_) {
      if (!ship.IsDestroyed())
        return false;
    }
    return true;
  }
  return false;
}

auto battleship::Engine::IsShipMapCreated() -> bool { return isShipMapCreated_; }

void battleship::Engine::SetShipMapCreated(bool value) {isShipMapCreated_ = value;}


void battleship::Engine::DrawShips() {
  cinder::gl::color(cinder::Color(1,0,0));
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
      //cinder::gl::color(cinder::Color::white());
      cinder::gl::color(cinder::Color(0.7,0.8,0.8));
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
void battleship::Engine::DrawMissile() {
  for (Location& location : attackLocations_) {
    cinder::gl::color(cinder::Color(1,1,0));
    for (Location& l : successfulAttackLocs_) {
      if (l == location) {
        cinder::gl::color(cinder::Color(0,1,0));
        break;
      }
    }
    battleship::Location loc = gameBoard_.LocationOnBoard(location);
    loc = loc.GetCenter();
    cinder::gl::drawSolidCircle({loc.Row(), loc.Col()}, 10);
  }
}

void Engine::Attack(vector<battleship::Location>& attackLocs, vector<Ship>& opponentBattleships) {
  opponent_ = opponentBattleships;
  for (Location& location : attackLocs) {
    attackLocations_.emplace_back(location);
    Attack(location, opponentBattleships);
  }
}


void Engine::SetShips(vector<Location>& shipLocations, vector<Direction>& shipDirections) {
  vector<battleship::Ship> battleships;
  battleships.reserve(shipLocations.size());
  for (int i = 0; i < shipLocations.size(); i++) {
    battleships.emplace_back(battleship::Ship(shipLocations.at(i),
                                               shipDirections.at(i)));
  }
  battleships_ = battleships;
}

} //namespace battleship