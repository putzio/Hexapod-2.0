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
    // virtual Result GoToPosition();
    virtual Result GoForeward();
    virtual Result GoBackward();
    virtual Result TurnRight();
    virtual Result TurnLeft();
    Result GoToTheDefaultPosition();
    /**
     * @brief returns an enum representing the class(WalkingMode)
     * 
     * @return ** Result enum Mode
     */
    virtual Mode GetWalkingMode();
    const LegContainer *GetTargetLegsPositionsPtr();

};