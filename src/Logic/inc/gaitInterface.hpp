#pragma once
#include "LegContainer.hpp"
#include "Results.h"

namespace logic::gait {

    class GaitInterface {
    public:
        typedef enum Gait {
            NONE,
            DEFAULT_POSITION,
            TRIPOD,
            CATEPILLAR,
            MONOCHROMATIC
        }Gait;

    protected:
        leg::LegContainer targetLegsPositions;
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
        virtual Result GoToTheDefaultPosition();
        virtual std::array<float, 2> GetChangingStepValues() = 0;
        /**
         * @brief returns an enum representing the classingMode)
         *
         * @return ** Result enum Mode
         */
        const leg::LegContainer* const GetTargetLegsPositionsPtr() const { return &targetLegsPositions; };
    };
} // namespace logic::gait

