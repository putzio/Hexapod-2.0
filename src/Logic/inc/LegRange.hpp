#pragma once
#include "..\..\..\include\Results.h"
#include "..\..\..\include\constants.hpp"
namespace logic::leg {
    typedef struct LegRange {
        float y[2];
        float x[2];

    private:
        inline bool ValueInRange(const float& value, const float range[2]) {
            return (value > range[0] && value < range[1]);
        }

    public:
        LegRange() {
            x[0] = Constants::X_ABSOLUTE_RANGE[0];
            x[1] = Constants::X_ABSOLUTE_RANGE[1];
            y[0] = Constants::Y_ABSOLUTE_RANGE[0];
            y[1] = Constants::Y_ABSOLUTE_RANGE[1];
        }
        Result NewHightRange_mm(const float& min, const float& max) {
            if (ValueInRange(min, Constants::Y_ABSOLUTE_RANGE) &&
                ValueInRange(max, Constants::Y_ABSOLUTE_RANGE) &&
                min < max) {
                y[0] = min;
                y[1] = max;
                return RESULT_OK;
            }
            else {
                return RESULT_HIGHT_OUT_OF_RANGE;
            }
        }
        Result NewHightRange_mm(float hightRange[2]) {
            return NewHightRange_mm(hightRange[0], hightRange[1]);
        }
    }LegRange;
}