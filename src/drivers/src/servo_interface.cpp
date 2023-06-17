#include "servo_interface.hpp"

namespace pico_drivers {
    void Servo_Interface::Calibrate(int16_t value) {
        calibrationValue = value;
    }

    uint16_t Servo_Interface::MapAngleToPwmTime(uint8_t angle) {
        return (double)(angle * (Constants::ANGLE_RANGE_MS[1] - Constants::ANGLE_RANGE_MS[0])) / 180.0 + Constants::ANGLE_RANGE_MS[0];
    }
}