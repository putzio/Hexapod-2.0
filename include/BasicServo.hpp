#pragma once
#include <stdint.h>

class BasicServo {
    protected:
    uint16_t currentPosition;
    uint16_t nextPosition;
};