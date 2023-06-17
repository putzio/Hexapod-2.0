#pragma once

#include "pwm.hpp"
#include "servo_interface.hpp"


namespace pico_drivers {
    class ServoLeft : public Servo_Interface {
    public:
        ServoLeft(uint8_t newPin);
        ~ServoLeft() { delete pwm; };
        void SetAngle(uint8_t angle) override;
        void SetRadianAngle(float angle) override;
        void Disable() override { pwm->Disable(); };
        // void TestPWM() { SetPwm(10000); Enable(); }
    };
}