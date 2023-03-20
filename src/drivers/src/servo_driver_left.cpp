#include "../inc/servo_driver_left.hpp"

void ServoDriverLeft::SetAngle(uint8_t angle) {
    uint16_t msTime = MapAngleToPwmTime(angle);
    pwmDriver->SetPwm(msTime);
    pwmDriver->Enable();
}

void ServoDriverLeft::SetRadianAngle(float angle) {
    SetAngle((uint8_t)(angle * 180.0 / 3.14));
}

ServoDriverLeft::ServoDriverLeft(uint8_t newPin) {
    pwmDriver = new Pwm_driver(newPin);
};