#pragma once
#include "gaitInterface.hpp"
#include "constants.hpp"
#include "Results.h"
#include "footCoordinates.hpp"
#include <array>

namespace logic::gait {
    class MetachromaticGait : public GaitInterface {
    public:
        void Error_Handler();
        MetachromaticGait();
        Result GoForeward() override;
        Result GoBackward() override;
        Result TurnRight() override;
        Result TurnLeft() override;
        // Result GoToTheDefaultPosition() override;
        Gait GetCurrentGait() override { return METACHROMATIC; };
    private:
        leg::SingleCoordinate xForeward = Constants::X_ABSOLUTE_RANGE[1];
        leg::SingleCoordinate xBackwards = Constants::X_ABSOLUTE_RANGE[0];
        leg::SingleCoordinate CalculateXTargetPosition(uint8_t step);
        std::array<leg::SingleCoordinate, 6> xPositions;
    };
} // namespace logic::gait