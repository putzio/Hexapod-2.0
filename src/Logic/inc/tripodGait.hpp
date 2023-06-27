#pragma once
#include "gaitInterface.hpp"
#include "constants.hpp"
#include "Results.h"
#include "FootCoordinates.hpp"

namespace logic::gait {
    class TripodGait : public GaitInterface {
    public:
        TripodGait() { step = 0; };
        Result GoForeward() override;
        Result GoBackward() override;
        Result TurnRight() override;
        Result TurnLeft() override;
        Result GoToTheDefaultPosition() override;
        Gait GetCurrentGait() override { return TRIPOD; };
        std::array<float, 2> GetChangingStepValues() override;
    private:
        leg::SingleCoordinate xForeward = Constants::X_ABSOLUTE_RANGE[1];
        leg::SingleCoordinate xBackwards = Constants::X_ABSOLUTE_RANGE[0];
        const float changingStepValues[2] = { Constants::DEFAULT_CHANGING_STEP, Constants::DEFAULT_CHANGING_STEP * 4 };
        uint8_t firstGroupOfLegs[3] = {
            leg::LegContainer::LEFT_FRONT,
            leg::LegContainer::RIGHT_MIDDLE,
            leg::LegContainer::LEFT_BACK
        };
        uint8_t secondGroupOfLegs[3] = {
            leg::LegContainer::RIGHT_FRONT,
            leg::LegContainer::LEFT_MIDDLE,
            leg::LegContainer::RIGHT_BACK
        };
        uint8_t leftLegs[3] = {
            leg::LegContainer::LEFT_FRONT,
            leg::LegContainer::LEFT_MIDDLE,
            leg::LegContainer::LEFT_BACK
        };
        uint8_t rightLegs[3] = {
            leg::LegContainer::RIGHT_FRONT,
            leg::LegContainer::RIGHT_MIDDLE,
            leg::LegContainer::RIGHT_BACK
        };
    };
} // namespace logic::gait