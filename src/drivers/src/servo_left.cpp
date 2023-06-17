#include "servo_left.hpp"

namespace pico_drivers {
    void ServoLeft::SetAngle(uint8_t angle) {
        uint16_t msTime = MapAngleToPwmTime(angle);
        pwm->SetPwm(msTime + calibrationValue);
        pwm->Enable();
    }

    void ServoLeft::SetRadianAngle(float angle) {
        SetAngle((uint8_t)(angle * 180.0f / 3.14f));
    }

    ServoLeft::ServoLeft(uint8_t newPin) {
        pwm = new Pwm(newPin);
    };
}