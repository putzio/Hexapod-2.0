#pragma once
#include "LegContainer.hpp"
#include "Results.h"

namespace logic::gait {
    class GaitInterface {
    public:
        typedef enum Gait {
            NONE,
            DEFAULT_POSITION,
            TRIPOD_WALK,
            CATEPILLAR_WALK,
            MONOCHROMATIC_WALKs
        }Gait;

    protected:
        leg::LegContainer targetLegsPositions;
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
        Gait GetCurrentGait() { return NONE; };
        const leg::LegContainer* const GetTargetLegsPositionsPtr() const { return &targetLegsPositions; };
    };
} // namespace logic::gait

