#pragma once

#include "gpio.hpp"
#include "legs_controller.hpp"
#include "robot_current_sensors.hpp"
#include "servo_left.hpp"
#include "servo_right.hpp"
#include "pinout.hpp"
#include "Results.h"
#include <array>

namespace pico_drivers {
    class RobotDriver {
    public:
        RobotDriver();
        std::array<uint16_t, 12> UpdateCurrentSensorsValues();
        void UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges);
        void CalibrateServos(const std::array<int16_t, 12>& calibrationValues);
    private:
        const std::array<uint8_t, 12> current_sensors_channels = { 7, 6, 4, 3, 1, 0, 1, 0, 3, 4, 6, 7 };
        RobotCurrentSensors current_sensors;
        LegsController legsController;
    };
}