#pragma once

#include <stdint.h>
#include <cmath>

#define PI 3.14159265

typedef struct ServosPositions{
  float UpperServoAngle;
  float LowerServoAngle;
  bool operator==(const ServosPositions& other)const{
    return abs(this->LowerServoAngle - other.LowerServoAngle) < 0.0001 && abs(this->UpperServoAngle - other.UpperServoAngle) < 0.0001;
  }
} ServosPositions;


class LegPositionController{  

    int16_t x;
    uint16_t y;
    // double H;
    public:
    const uint16_t yRange[2] = {12000, 17000};
    const int16_t xRange[2] = {-5285, 2857};

    public:
    LegPositionController();
    LegPositionController(int16_t xPos, uint16_t yPos);

    int16_t GetX();
    uint16_t GetY();

    void CalculateYPosition(const int16_t &xPos);    
    uint16_t MapXInRange(const int16_t &xPos);
    /**
      *   \brief Calculate the servomotors positions
      *   
      *   \param newX, newY the position of the end of the leg.
      *   The point (0,0) is in the Upper servomotor joint
      *   \return struct ServoPositions with values of angles for both servomotors
      *
      **/
    ServosPositions CalculateServoPositions(int16_t newX, uint16_t newY);
};