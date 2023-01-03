#pragma once

#include "Logic/LegPositionController.hpp"
#include "Logic/WalkingModes/LegContainer.hpp"
#include "Results.h"

class WalkingInterface{
    public:
    typedef enum Mode{
        NONE,
        DEFAULT_POSITION,
        TRIPOD_WALK,
        CATEPILLAR_WALK,
        MONOCHROMATIC_WALK
    }Mode;
    
    protected:
    LegContainer *targetLegsPositions;
    Coordinates *currentLegsCoordinates[6];
    uint8_t step = 0;

    public:
    /**
     * @brief depending on the walking mode and the step
     *        the targetLegsPositions variable is set
     * 
     *      If the position is achieved, the new positions are set   
     * 
     * @return ** Result 
     */
    virtual Result GoToPosition();
    // virtual void GoForeward();
    // virtual void GoBackward();
    // virtual void TurnRight();
    // virtual void TurnLeft();
    virtual Mode GetWalkingMode();
    const LegContainer *GetTargetLegsPositionsPtr();

};