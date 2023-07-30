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
    };
} // namespace logic::gait