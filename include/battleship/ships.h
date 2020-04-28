//
// Created by Kanav Khanna on 4/26/20.
//

#ifndef FINALPROJECT_SHIPS_H
#define FINALPROJECT_SHIPS_H

#include <vector>

#include "ship.h"
namespace battleship {

class Ships {
 private:
  vector<Ship> battleships_;
  vector<Location> attackLocations_;

 public:
  Ships();
  Ships(vector<Ship> battleships);

  //return the ship at a specific location
  Ship GetShip(Location location);

  //attacks the opponent's ship
  void Attack(Location location, vector<Ship> opponentBattleships);

  // returns the locations the user has already attacked
  vector<Location> GetAttackedLocations();

  //checks if a location is attacked or not
  bool IsAttacked(Location location);

  //returns whether all the ships are destroyed or not
  bool IsGameOver();

  //resets the player's ships
  void Reset();

  //sets the ships locations
  void SetShipsLocation();

  Location GetShipSetLocation();

  Direction GetShipSetDirection();

};

}

#endif  // FINALPROJECT_SHIPS_H
