#pragma once

#include <cmath>
// # include "Logic/WalkingModes/LegContainer.hpp"

typedef struct Coordinates{
  float x,y;
  bool operator==(const Coordinates& other)const{
    return std::abs(this->x - other.x) < 0.0001 && std::abs(this->y - other.y) < 0.0001;
  }
  bool operator!=(const Coordinates& other)const{
    return !(*this == other);
  }
}Coordinates;

typedef struct LegsCoordinates
{
    Coordinates coordinates[6];

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
