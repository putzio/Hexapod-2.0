#pragma once
#include <stdint.h>

class BasicServo {
    protected:
    uint16_t nextPosition;
    public:
    bool enabled;
    uint16_t currentPosition;//private???
};