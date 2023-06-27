#include "leg_controller.hpp"

namespace pico_drivers {
    LegController::LegController(std::array<uint8_t, 12> pins) {
        for (int i = 0; i < pins.size() / 2; i++) {
            if (i % 2 == 0) {
                servos[2 * i] = std::make_unique<ServoLeft>(pins[2 * i]);
                servos[2 * i + 1] = std::make_unique<ServoLeft>(pins[2 * i + 1]);
            }
            else {
                servos[2 * i] = std::make_unique<ServoRight>(pins[2 * i]);
                servos[2 * i + 1] = std::make_unique<ServoRight>(pins[2 * i + 1]);
            }
        }
    }
    void LegController::InitServos() {
        for (int i = 0; i < servos.size(); i++) {
            servos[i]->SetAngle(90);
        }
    }
    void LegController::UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges) {
        for (int i = 0; i < newAnges.size(); i++) {
            servos[i * 2]->SetRadianAngle(newAnges[i].upperServoAngle);
            servos[i * 2 + 1]->SetRadianAngle(newAnges[i].lowerServoAngle);
        }
    }

} // namespace pico_drivers