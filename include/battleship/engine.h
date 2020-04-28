//
// Created by Kanav Khanna on 4/26/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <cstddef>
#include <random>
#include <vector>

#include "board.h"
#include "ship.h"

namespace battleship {

// This is the game engine which is primary way to interact with the game.
class Engine {
 private:
  size_t width_;
  size_t height_;
  size_t tile_size_;
  vector<Location> attackLocations_;
  std::mt19937 rng_;
  std::uniform_real_distribution<double> uniform_;
  bool isShipMapCreated_ = false;
  battleship::Board gameBoard_;

 public:
  // Creates a new battleship game of the given size.
  Engine(size_t width, size_t height,size_t tile_size_);

  // Creates a new battleship game of the given size, seeded.
  Engine(size_t width, size_t height,size_t tile_size_, unsigned seed);

  // Start the game over.
  void Reset();

  // Play the game
  void PlayGame();

  //attacks the opponent's ship
  void Attack(Location location, const vector<Ship>& opponentBattleships);

  // returns the locations the user has already attacked
  vector<Location> GetAttackedLocations();

  //checks if a location is attacked or not
  auto IsAttacked(Location location) -> bool;

  //returns whether all the ships are destroyed or not
  bool IsGameOver();

  //sets the ships locations
  void SetShipLocation(battleship::Location location, battleship::Direction direction);

  //gets the location of where to set the ship
  auto GetLocationForShip() -> Location;

  //gets the orientation of the ship to set
  Direction GetDirectionForShip();

  auto GetShip(Location location) -> Ship;

  auto IsShipMapCreated() -> bool;

  void SetShipMapCreated(bool value);

  vector<Ship> battleships_;

  void AddShip(Location location, Direction direction);

  void DrawShips();

  void DrawMap();
};

}

#endif  // FINALPROJECT_ENGINE_H
