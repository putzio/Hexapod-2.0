#pragma once

#include <stdint.h>
#include <cmath>
#include "constants.hpp"

typedef struct ServosPositions{
  float upperServoAngle;
  float lowerServoAngle;
  bool operator==(const ServosPositions& other)const{
    return abs(this->lowerServoAngle - other.lowerServoAngle) < 0.0001 && abs(this->upperServoAngle - other.upperServoAngle) < 0.0001;
  }
} ServosPositions;

typedef struct Coordinates{
  float x,y;
  bool operator==(const Coordinates& other)const{
    return abs(this->x - other.x) < 0.0001 && abs(this->y - other.y) < 0.0001;
  }
  bool operator!=(const Coordinates& other)const{
    return !(*this == other);
  }
}Coordinates;


class LegPositionController{  
    private:
    Coordinates p_coordinates;

    public:
    const float *yRange = Constants::Y_ABSOLUTE_RANGE;
    const float *xRange = Constants::X_ABSOLUTE_RANGE;

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
    ServosPositions CalculateServoPositions(const Coordinates &coordinates);

    float GetX();
    float GetY();
    Coordinates GetCoordinates();

    /**
    *   \brief Set current xy position
    *   
    *   \param newX, newY the position of the end of the leg.
    *   The point (0,0) is in the Upper servomotor joint
    *
    **/
    void SetNewXYPosition(float xNew, float yNew);
    void SetNewXYPosition(const Coordinates &coordinates);
    

    /**
    *   \brief Find the xy position based on the servomotors
    *   angles and write it to the p_coordinates
    *   
    *   \param positions resference to the servomotors positions
    *
    **/
    void FindXYPosition(const ServosPositions& positions);
    private:
    void SetX(float xNew);
    void SetY(float yNew);
};