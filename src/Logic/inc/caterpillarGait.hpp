#pragma once
#include "gaitInterface.hpp"
#include "constants.hpp"
#include "Results.h"
#include "FootCoordinates.hpp"

namespace logic::gait {
    class CaterpillarGait : public GaitInterface {
    public:

        void Error_Handler();
        CaterpillarGait() {
            step = 0;
            changingStepValues[0] = Constants::DEFAULT_CHANGING_STEP / 2.0;//On ground 
            changingStepValues[1] = Constants::DEFAULT_CHANGING_STEP * 2.0;//In air 
        };
        Result GoForeward() override;
        Result GoBackward() override;
        Result TurnRight() override;
        Result TurnLeft() override;
        Result GoToTheDefaultPosition() override;
        Gait GetCurrentGait() override { return CATERPILLAR; };
    private:
        leg::SingleCoordinate xForeward = Constants::X_ABSOLUTE_RANGE[1];
        leg::SingleCoordinate xBackwards = Constants::X_ABSOLUTE_RANGE[0];
        leg::SingleCoordinate xHalfway = xForeward + xBackwards / 2;
        uint8_t frontLegs[2] = {
            leg::LegContainer::LEFT_FRONT,
            leg::LegContainer::RIGHT_FRONT
        };
        uint8_t middleLegs[2] = {
            leg::LegContainer::LEFT_MIDDLE,
            leg::LegContainer::RIGHT_MIDDLE
        };
        uint8_t backLegs[2] = {
            leg::LegContainer::LEFT_BACK,
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
        leg::FootTargetPosition liftAndForeward = { xForeward, false };
        leg::FootTargetPosition lowerAndHalfway = { xHalfway, true };
        leg::FootTargetPosition lowerAndBackward = { xBackwards, true };
        leg::FootTargetPosition liftAndBackward = { xBackwards, false };
        leg::FootTargetPosition lowerAndForeward = { xForeward, true };
    };
} // namespace logic::gait