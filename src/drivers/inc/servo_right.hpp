#pragma once

#include "servo_interface.hpp"
#include "pwm.hpp"

namespace pico_drivers {
    class ServoRight : public Servo_Interface, public Pwm {
    public:
        ServoRight(uint8_t newPin) : Pwm(newPin) {}
        void SetAngle(uint8_t angle) override;
        // void TestPWM() { SetPwm(10000); Enable(); }
    };
}