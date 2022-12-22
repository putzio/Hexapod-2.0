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
    private:
    int16_t x;
    uint16_t y;

    public:
    const uint16_t yRange[2] = {12000, 17000};
    const int16_t xRange[2] = {-5285, 2857};

    public:
    LegPositionController();
    LegPositionController(int16_t xPos, uint16_t yPos);

    /**
      *   \brief Calculate the y position when the leg is up
      *   When the leg is up, the foot's path is a sin function
      *   
      *   \param xPos the x position of the end of the leg
      *   The point (0,0) is in the Upper servomotor joint
      *   \return struct ServoPositions with values of angles for both servomotors
      *
      **/
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
    ServosPositions CalculateServoPositions(int16_t xNew, uint16_t yNew);

    int16_t GetX();
    uint16_t GetY();
    void SetNewXYPosition(int16_t xNew, uint16_t yNew);
    
    void FindXYPosition(const ServosPositions& positions);
    private:
    void SetX(int16_t xNew);
    void SetY(uint16_t yNew);
};