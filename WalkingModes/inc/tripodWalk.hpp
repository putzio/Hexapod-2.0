#pragma once

#include "../inc/walkingInterface.hpp"
// #include"Results.h"

class TripodWalk: public WalkingInterface {

protected:
    // LegContainer p_positions[2];
public:
    TripodWalk();
    Result GoForeward()override;
    Result GoBackward()override;
    Result TurnRight()override;
    Result TurnLeft()override;

    //From the front left leg perspective 
    //LegContainer Set...()???
    void SetPositionBackDown(LegContainer& legContainer);
    void SetPositionBackUp(LegContainer& legContainer);
    void SetPositionFrontUp(LegContainer& legContainer);
    void SetPositionFrontDown(LegContainer& legContainer);
    LegContainer ReturnSetPosition(void (TripodWalk::* SetPositionFunctionPtr)(LegContainer&));

    Mode GetWalkingMode()override;

};