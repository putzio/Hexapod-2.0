#pragma once
#include <stdint.h>

class BasicServo {
    public:
    bool enabled;
    uint16_t currentPosition;//private???
    void EnableServo(){
        enabled=true;
    }
};