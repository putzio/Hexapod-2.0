#pragma once

#include "constants.hpp"
#include "pwm.hpp"


namespace pico_drivers {
    class Servo_Interface {
    protected:
        int16_t calibrationValue = 0;
        Pwm* pwm;
        uint16_t MapAngleToPwmTime(uint8_t angle);
    public:
        virtual void SetAngle(uint8_t angle);
        virtual void SetRadianAngle(float angle);
        void Calibrate(int16_t value);
        virtual void Disable();
    };
}