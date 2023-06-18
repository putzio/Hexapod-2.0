#include "servo_right.hpp"

namespace pico_drivers {
    void ServoRight::SetAngle(uint8_t angle) {
        uint16_t msTime = MapAngleToPwmTime(180 - angle);
        SetPwm(msTime + calibrationValue);
        Enable();
    }
}