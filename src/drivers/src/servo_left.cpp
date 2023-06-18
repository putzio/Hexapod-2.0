#include "servo_left.hpp"

namespace pico_drivers {
    void ServoLeft::SetAngle(uint8_t angle) {
        uint16_t msTime = MapAngleToPwmTime(angle);
        SetPwm(msTime + calibrationValue);
        Enable();
    }
}