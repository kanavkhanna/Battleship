//
// Created by Kanav Khanna on 4/25/20.
//

#ifndef FINALPROJECT_SEGMENT_H
#define FINALPROJECT_SEGMENT_H
#include "Location.h"
namespace battleship {

class Segment {
 private:
  Location location_;
  bool visible_;


 public:
  explicit Segment(const Location& location);
  Location GetLocation() const;
  Location SetLocation(const Location&);
  void SetVisibility(bool visible);
  bool IsVisibile() const;
};

} // namespace battleship

#endif  // FINALPROJECT_SEGMENT_H
