// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <battleship/direction.h>
#include <battleship/engine.h>
#include <battleship/Location.h>
#include <cinder/Rand.h>
#include <mylibrary/example.h>

#include <catch2/catch.hpp>

using battleship::Direction;
using battleship::Engine;
using battleship::Location;
using battleship::Board;


TEST_CASE("Location vector operations", "[location]") {
  SECTION("Sum") {
    Location loc1{12, 9};
    Location loc2{7, 3};

    Location result = loc1 + loc2;
    REQUIRE(result == Location{19, 12});
  }

  SECTION("Difference") {
    Location loc1{-1, 3};
    Location loc2{7, 2};

    Location result = loc1 - loc2;
    REQUIRE(result == Location{-8, 1});
  }

  SECTION("Division") {
    Location loc1{30, 60};

    Location result = loc1/3;
    REQUIRE(result == Location{10, 20});
  }
}

TEST_CASE("Board operations", "[board]") {
  Board board = Board(30, 27);

  SECTION("Board size") {
    REQUIRE(board.BoardSize() == 27*27);
  }

  SECTION("Location on board") {
    Location window_loc = Location(129,79);
    Location board_loc = board.LocationOnBoard(window_loc);
    REQUIRE(board_loc == Location(4,2));
  }
}

TEST_CASE("Creating ships", "[engine][ship]") {
  Engine engine = Engine("p1",10,10,30);

  vector<Location> locations{Location(133,89), Location(144, 108),
                             Location(44, 190)};

  vector<Direction> directions{Direction::kDown, Direction::kDown, Direction::kRight};

  engine.SetShips(locations, directions);

  SECTION("Ship Size") {
    REQUIRE(engine.battleships_.size() == 3);
  }

  SECTION("Ship Head Location") {
    battleship::Ship ship = engine.battleships_.at(2);
    REQUIRE(ship.Head().GetLocation() == Location(44,190));
  }

}