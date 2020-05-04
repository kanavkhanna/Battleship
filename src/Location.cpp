//
// Created by Kanav Khanna on 4/25/20.
//

#include "battleship/Location.h"

namespace battleship {

Location::Location(int row, int col) : row_(row), col_(col) {}

int Location::Row() const { return row_; }

int Location::Col() const { return col_; }

bool Location::operator==(const Location& rhs) const {
  return row_ == rhs.row_ && col_ == rhs.col_;
}

bool Location::operator()(const Location& lhs, const Location& rhs) const {
  return lhs <= rhs;
}

bool Location::operator!=(const Location& rhs) const {
  return !(*this == rhs);
}

bool Location::operator<(const Location& rhs) const {
  return row_ < rhs.row_ || (rhs.row_ >= row_ && col_ < rhs.col_);
}

bool Location::operator<=(const Location& rhs) const {
  return !(rhs < *this);
}

bool Location::operator>(const Location& rhs) const {
  return rhs < *this;
}

bool Location::operator>=(const Location& rhs) const {
  return !(*this < rhs);
}

Location const Location::operator+(const Location& rhs) const {
  return { row_ + rhs.row_, col_ + rhs.col_ };
}

Location const Location::operator-(const Location& rhs) const {
  return *this + (-rhs);
}

Location Location::operator-() const { return {-row_, -col_}; }

Location& Location::operator+=(const Location& rhs) {
  *this = *this + rhs;
  return *this;
}

int mod(int a, int b) {
  int c = a % b;
  return c + (c < 0 ? b : 0);
}

Location Location::operator%(const Location& rhs) const {
  return {mod(row_, rhs.row_), mod(col_, rhs.col_)};
}

auto Location::GetCenter() -> Location {
  int x = row_, y = col_;
  return {x*30+15,y*30+15};
}

Location Location::operator/(const int toDivide) {
  return {(row_)/toDivide,
          (col_)/toDivide};
}

std::ostream& operator<<(std::ostream& os, const Location& location) {
  os << "{row=" << location.Row() << ", col=" << location.Col() << "}";
  return os;
}

}// namespace battleship