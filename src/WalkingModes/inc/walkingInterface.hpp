#pragma once

#include "../../Logic/inc/LegPositionControllerInterface.hpp"
#include "LegContainer.hpp"
#include "..\..\..\include\Results.h"
#include "..\..\..\include\constants.hpp"

class WalkingInterface {
public:
    typedef enum Mode {
        NONE,
        DEFAULT_POSITION,
        TRIPOD_WALK,
        CATEPILLAR_WALK,
        MONOCHROMATIC_WALK
    }Mode;

protected:
    LegContainer* targetLegsPositions;
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
    const LegContainer* GetTargetLegsPositionsPtr();

};