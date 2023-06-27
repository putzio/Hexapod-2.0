#pragma once
#include <stdint.h>
#include <math.h>

namespace Constants {
    // mathematical constants
    const double PI = 3.14159265;

    // phisical properties
    const uint8_t LEG_LENGTH = 70;
    //Distance in the x axis for calculating the next positions by LegpositionController object
    const float DELTA_X_MM = 1;//mm
    const float DELTA_X = DELTA_X_MM / (float)LEG_LENGTH;
    // Absolute ranges of the servo movements
    const float X_ABSOLUTE_RANGE[2] = { -0.5285, 0.2857 };
    const float Y_ABSOLUTE_RANGE[2] = { 1.2f, 2.0 };//sin(60.0 * Constants::PI / 180.0) * 20000.0 = 1.7320f?

    // angle ranges
    const float ANGLE_RANGE[2] = { 0, PI };
    const uint16_t ANGLE_RANGE_MS[2] = { 500, 2500 };

    const float DEFAULT_LEG_HIGHT = (sin(60.0 * PI / 180.0) * 2.0);

    const float CHANGING_STEP_RANGE[2] = { PI * 0.1f / 180.0f , PI * 10.0f / 180.0f }; //0.1 to 10 deg
    const float DEFAULT_CHANGING_STEP = PI * 0.3 / 180.0f;
} // namespace Constants




