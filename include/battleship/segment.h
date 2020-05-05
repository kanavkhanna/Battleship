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
  explicit Segment(Location location);

  //returns the location of the segment
  Location GetLocation();

  //sets the visibility of the segment
  void SetVisibility(bool visible);

  //checks the visibility of the segment
  bool IsVisibile() const;
};

} // namespace battleship

#endif  // FINALPROJECT_SEGMENT_H
