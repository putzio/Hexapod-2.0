#pragma once
#include <cmath>

namespace logic::leg {
    typedef struct ServosPositions {
        float upperServoAngle;
        float lowerServoAngle;
        bool Equals(const ServosPositions& other) const {
            return abs(this->lowerServoAngle - other.lowerServoAngle) < 0.0001 && abs(this->upperServoAngle - other.upperServoAngle) < 0.0001;
        }
        bool operator==(const ServosPositions& other) const {
            return Equals(other);
        }
    }ServosPositions;
}