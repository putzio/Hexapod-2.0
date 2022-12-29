#pragma once

#include <stdint.h>
#include <cmath>
#include "constants.h"

typedef struct ServosPositions{
  float UpperServoAngle;
  float LowerServoAngle;
  bool operator==(const ServosPositions& other)const{
    return abs(this->LowerServoAngle - other.LowerServoAngle) < 0.0001 && abs(this->UpperServoAngle - other.UpperServoAngle) < 0.0001;
  }
} ServosPositions;


class LegPositionController{  
    private:
    float x;
    float y;

    public:
    const float yRange[2] = {1.2, 1.7};
    const float xRange[2] = {-0.5285, 0.2857};

    public:
    LegPositionController();
    LegPositionController(float xPos, float yPos);

    /**
      *   \brief Calculate the y position when the leg is up
      *   When the leg is up, the foot's path is a sin function
      *   
      *   \param xPos the x position of the end of the leg
      *   The point (0,0) is in the Upper servomotor joint
      *   \return struct ServoPositions with values of angles for both servomotors
      *
      **/
    void CalculateYPosition(const float &xPos);  

    float MapXInRange(const float &xPos);
    /**
      *   \brief Calculate the servomotors positions
      *   
      *   \param newX, newY the position of the end of the leg.
      *   The point (0,0) is in the Upper servomotor joint
      *   \return struct ServoPositions with values of angles for both servomotors
      *
      **/
    ServosPositions CalculateServoPositions(float xNew, float yNew);

    float GetX();
    float GetY();
    void SetNewXYPosition(float xNew, float yNew);
    
    void FindXYPosition(const ServosPositions& positions);
    private:
    void SetX(float xNew);
    void SetY(float yNew);
};