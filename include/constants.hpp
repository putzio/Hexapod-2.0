#pragma once
#include <stdint.h>

namespace Constants
{
    // mathematical constants
    const double PI = 3.14159265;

    // phisical properties
    const uint8_t LEG_LENGTH = 70;
    //Distance in the x axis for calculating the next positions by LegpositionController object
    const float DELTA_X = 5;//mm
    // Absolute ranges of the servo movements
    const float X_ABSOLUTE_RANGE[2] = {-0.5285, 0.2857};
    const float Y_ABSOLUTE_RANGE[2] = {1.2,1.7};

    // angle ranges
    const float ANGLE_RANGE [2] = {0, PI};
    const uint16_t ANGLE_RANGE_MS[2] = {500, 2500};
} // namespace Constants




