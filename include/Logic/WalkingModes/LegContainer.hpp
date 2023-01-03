#pragma once
#include <cmath>
#include "Logic/LegPositionController.hpp"

typedef struct SimplifiedLeg{
    float x;
    bool legUp;
    bool operator==(const SimplifiedLeg &leg)const;
    bool operator!=(const SimplifiedLeg &leg)const;
    bool operator==(const Coordinates &leg)const;
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
};