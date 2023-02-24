#pragma once
#include <cmath>
// #include "LegPositionControllerInterface.hpp"
#include "../../Logic/inc/FootCoordinates.hpp"

typedef struct SimplifiedLeg{
    float x;
    bool legUp;
    bool operator==(const SimplifiedLeg &leg)const;
    bool operator!=(const SimplifiedLeg &leg)const;
    bool operator==(const FootCoordinates &leg)const;
    bool operator!=(const FootCoordinates &leg)const;
    void SetLeg(float x, bool legUp){
        this->x = x;
        this->legUp = legUp;
    }
}SimplifiedLeg;

struct LegContainer{
    SimplifiedLeg legs[6];
    enum LegPositions{
        LEFT_FRONT,
        RIGHT_FRONT,
        LEFT_MIDDLE,
        RIGHT_MIDDLE,
        LEFT_BACK,
        RIGHT_BACK
    };
    bool operator==(const LegContainer &legContainer)const;
    bool operator==(const LegsCoordinates &legCoordinates)const;
    bool LegContainerEqualsToCoordinates(const LegsCoordinates &legCoordinates)const;
};