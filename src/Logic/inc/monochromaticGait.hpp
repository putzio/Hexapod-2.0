#pragma once
#include "gaitInterface.hpp"
#include "constants.hpp"
#include "Results.h"
#include "FootCoordinates.hpp"
#include <array>

namespace logic::gait {
    class MonochromaticGait : public GaitInterface {
    public:

        void Error_Handler();
        MonochromaticGait();
        Result GoForeward() override;
        Result GoBackward() override;
        Result TurnRight() override;
        Result TurnLeft() override;
        Result GoToTheDefaultPosition() override;
        Gait GetCurrentGait() override { return MONOCHROMATIC; };
    private:
        leg::SingleCoordinate xForeward = Constants::X_ABSOLUTE_RANGE[1];
        leg::SingleCoordinate xBackwards = Constants::X_ABSOLUTE_RANGE[0];
        leg::SingleCoordinate CalculateXTargetPosition(uint8_t step);
        std::array<leg::SingleCoordinate, 6> xPositions;
        // uint8_t frontLegs[2] = {
        //     leg::LegContainer::LEFT_FRONT,
        //     leg::LegContainer::RIGHT_FRONT
        // };
        // uint8_t middleLegs[2] = {
        //     leg::LegContainer::LEFT_MIDDLE,
        //     leg::LegContainer::RIGHT_MIDDLE
        // };
        // uint8_t backLegs[2] = {
        //     leg::LegContainer::LEFT_BACK,
        //     leg::LegContainer::RIGHT_BACK
        // };
        // uint8_t leftLegs[3] = {
        //     leg::LegContainer::LEFT_FRONT,
        //     leg::LegContainer::LEFT_MIDDLE,
        //     leg::LegContainer::LEFT_BACK
        // };
        // uint8_t rightLegs[3] = {
        //     leg::LegContainer::RIGHT_FRONT,
        //     leg::LegContainer::RIGHT_MIDDLE,
        //     leg::LegContainer::RIGHT_BACK
        // };
    };
} // namespace logic::gait