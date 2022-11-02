#pragma once
#include "Logic/Leg.hpp"
#include "ListOfSteps.h"
#include "enum_types.h"

/*
    Leg arrangement:
              ____
    leg 0   -|    |-    leg 1
    leg 2   -|    |-    leg 3
    leg 4   -|____|-    leg 5
*/
class Body
{
protected:
    uint8_t legTeam1[3] = {0, 3, 4};
    uint8_t legTeam2[3] = {1, 2, 5};
    State movingStates[ARRAY_SIZE(forwardStates)];
    Leg legs[6];
    uint8_t slowModeLegMove = 0; // leg:0-5 is movedover the ground
public:
    Mode modeType = StopMode;
    int step = 0;
    bool reset = false;
    Body();
    void ChangeBodyVelocityLimits(int vMin, int vMax);
    void ChangeToForward();
    void ChangeToBack();
    void ChangeToLeft();
    void ChangeToRight();
    void ChangeToStop();
    void ChangeToReset();
    void ChangeToResetTemp();
    void ChangeTo90();
    void Move();
    bool MovesDone();
    void ModeChanged(Mode s);
    void DisableLegs();
};