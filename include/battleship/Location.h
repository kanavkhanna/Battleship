//
// Created by Kanav Khanna on 4/25/20.
//

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H

#include <cstddef>
#include <iostream>

namespace battleship {

// Represents a location on the board.
class Location {
 private:
  int row_;
  int col_;

 public:
  Location(int row, int col);

  //Accessors
  int Row() const;
  int Col() const;

  // Comparison operators.
  bool operator()(const Location& lhs, const Location& rhs) const;
  bool operator==(const Location& rhs) const;
  bool operator!=(const Location& rhs) const;
  bool operator<(const Location& rhs) const;
  bool operator<=(const Location& rhs) const;
  bool operator>(const Location& rhs) const;
  bool operator>=(const Location& rhs) const;

  // Vector operators.
  Location const operator+(const Location& rhs) const;
  // Note: Always returns positive coordinates.
  Location operator%(const Location& rhs) const;
  Location const operator-(const Location& rhs) const;
  Location& operator+=(const Location& rhs);
  Location operator/(const int toDivide);
  Location operator-() const;

  //returns the center of the tile
  auto GetCenter() -> Location;

};

std::ostream& operator<<(std::ostream& os, const Location& location);

} // namespace battleship

#endif  // FINALPROJECT_LOCATION_H
