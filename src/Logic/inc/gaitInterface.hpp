#pragma once
#include "LegContainer.hpp"
#include "Results.h"
#include "array"

namespace logic::gait {

    typedef enum Gait {
        NONE,
        DEFAULT_POSITION,
        TRIPOD,
        CATERPILLAR,
        METACHROMATIC
    }GaitType;

    class GaitInterface {
    public:


    protected:
        leg::LegContainer targetLegsPositions;
        std::array<float, 2> changingStepValues{ {0,0} };
        // uint8_t step = 0;

    public:
        uint8_t step = 0;
        /**
         * @brief depending on theing mode and the step
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
        virtual Gait GetCurrentGait();
        Result GoToTheDefaultPosition() {
            leg::FootTargetPosition target;
            target.x = 0;
            target.footOnGround = true;
            for (leg::FootTargetPosition& legTarget : targetLegsPositions.legs) {
                legTarget = target;
            }
        };

        std::array<float, 2> GetChangingStepValues() { return changingStepValues; };
        /**
         * @brief returns an enum representing the classingMode)
         *
         * @return ** Result enum Mode
         */
        const leg::LegContainer* const GetTargetLegsPositionsPtr() const { return &targetLegsPositions; };
    };
} // namespace logic::gait

