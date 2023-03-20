#pragma once

#include <cmath>
// # include "Logic/WalkingModes/LegContainer.hpp"

typedef struct FootTargetPosition {
  float x;
  bool footOnGround;
  FootTargetPosition(float x = 0, bool footOnGround = true) { this->x = x;this->footOnGround = footOnGround; };
}FootTargetPosition;

typedef struct FootCoordinates {
  float x, y;
  void SetCoordinates_mm(const float& x, const float& y) {
    this->x = x / Constants::LEG_LENGTH;
    this->y = y / Constants::LEG_LENGTH;
  }
  float GetX_mm()const {
    return x * Constants::LEG_LENGTH;
  }
  float GetY_mm()const {
    return y * Constants::LEG_LENGTH;
  }

  bool operator==(const FootCoordinates& other)const {
    return std::abs(this->x - other.x) < 0.0001 && std::abs(this->y - other.y) < 0.0001;
  }
  bool operator!=(const FootCoordinates& other)const {
    return !(*this == other);
  }
  FootCoordinates operator/(const float& other) {
    x = x / other;
    y /= other;
    return *this;
  }
  FootCoordinates operator/=(const float& other) {
    *this = *this / other;
    return *this;
  }
  bool IsBetween(const float xRange[2], const float yRange[2])const {
    if (x<xRange[0] || x>xRange[1]) {
      return false;
    }
    if (y<yRange[0] || y>yRange[1]) {
      return false;
    }
    return true;
  }
}FootCoordinates;

typedef struct LegsCoordinates {
  FootCoordinates coordinates[6];

  // bool operator==(const LegsCoordinates &coordinates)const{
  //   for(int i = 0; i < 6; i++){
  //     if(legs[i] != legCoordinates.coordinates[i]){
  //         return false;
  //     }
  //   }
  //   return true;
  // }
  // bool operator!=(const LegsCoordinates &coordinates)const{
  //   return !(coordinates == *this);
  // }

}LegsCoordinates;
