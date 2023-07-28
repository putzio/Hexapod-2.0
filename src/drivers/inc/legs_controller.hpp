#pragma once
#include "servo_left.hpp"
#include "servo_right.hpp"
#include "ServoPositions.hpp"
#include <array>
#include <memory>

namespace pico_drivers {
    class LegsController {
        std::array<std::unique_ptr<Servo_Interface>, 12> servos;
    public:
        LegsController() {};
        LegsController(std::array<uint8_t, 12> pins);
        void InitServos();
        void UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges);

    };
} // namespace pico_drivers
