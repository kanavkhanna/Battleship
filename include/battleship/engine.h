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
  vector<Location> successfulAttackLocs_;
  battleship::Board gameBoard_;

  void Attack(Location location, vector<Ship>& opponentBattleships);

 public:
  // Creates a new battleship game of the given size.
  Engine(std::string,size_t width, size_t height,size_t tile_size_);

  // Creates a new battleship game of the given size, seeded.
  Engine(std::string,size_t width, size_t height,size_t tile_size_, unsigned seed);

  // Start the game over.
  void Reset();

  //attacks the opponent's ships
  void Attack(vector<battleship::Location>&, vector<Ship>& opponentBattleships);

  //returns whether all the ships are destroyed or not
  bool IsGameOver();

  //sets the ships of the player
  void SetShips(vector<Location>&, vector<Direction>&);

  auto IsShipMapCreated() -> bool;

  void SetShipMapCreated(bool value);

  vector<Ship> battleships_;

  void DrawShips();

  void DrawMap();

  void DrawMissile();

  bool showAttackLocs_ = false;

  const std::string player_name_;
};

}  // namespace battleship

#endif  // FINALPROJECT_ENGINE_H
