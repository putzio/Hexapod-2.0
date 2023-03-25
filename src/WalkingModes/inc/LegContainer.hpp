#pragma once
#include <cmath>
// #include "LegPositionController.hpp"
#include "../../Logic/inc/FootCoordinates.hpp"


struct LegContainer {
    FootTargetPosition legs[6];
    enum LegPositions {
        LEFT_FRONT,
        RIGHT_FRONT,
        LEFT_MIDDLE,
        RIGHT_MIDDLE,
        LEFT_BACK,
        RIGHT_BACK
    };
    bool operator==(const LegContainer& legContainer)const;
    bool operator==(const LegsCoordinates& legCoordinates)const;
    bool LegContainerEqualsToCoordinates(const LegsCoordinates& legCoordinates)const;
};