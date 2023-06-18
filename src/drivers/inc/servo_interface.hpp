#pragma once

#include "constants.hpp"


namespace pico_drivers {
    class Servo_Interface {
    protected:
        int16_t calibrationValue = 0;
        uint16_t MapAngleToPwmTime(uint8_t angle);
    public:
        virtual void SetAngle(uint8_t angle) = 0;
        void SetRadianAngle(float angle);
        void Calibrate(int16_t value);
    };
}