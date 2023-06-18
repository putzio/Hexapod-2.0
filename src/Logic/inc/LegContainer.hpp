#pragma once
#include <cmath>
// #include "LegPositionController.hpp"
#include "../../Logic/inc/FootCoordinates.hpp"
#include <array>

namespace logic::leg {
    struct LegContainer {
        std::array<FootTargetPosition, 6> legs;
        enum LegPositions {
            LEFT_FRONT,
            RIGHT_FRONT,
            LEFT_MIDDLE,
            RIGHT_MIDDLE,
            LEFT_BACK,
            RIGHT_BACK
        };
        bool operator==(const LegContainer& legContainer)const;
        // bool operator==(const LegsCoordinates& legCoordinates)const;
        // bool LegContainerEqualsToCoordinates(const LegsCoordinates& legCoordinates)const;
    };
}