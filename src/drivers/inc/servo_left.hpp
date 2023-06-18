#pragma once

#include "pwm.hpp"
#include "servo_interface.hpp"


namespace pico_drivers {
    class ServoLeft : public Servo_Interface, Pwm {
    public:
        ServoLeft(uint8_t newPin) : Pwm(newPin) {};
        ~ServoLeft() {};
        void SetAngle(uint8_t angle);
        // void TestPWM() { SetPwm(10000); Enable(); }
    };
}