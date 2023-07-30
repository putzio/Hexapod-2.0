#include "hexapod.hpp"
#include <string>

void Hexapod::PeriodicProcess() {
    std::array<uint16_t, 12> sensorData = driver.UpdateCurrentSensorsValues();
    std::string data;
    for (uint16_t measurement : sensorData) {
        // printf("%d;", measurement);
        data += std::to_string(measurement) + ";";
    }
    data += "\r\n";
    printf(data.c_str());
    gaitController.PeriodicProcess();
    driver.UpdateServos(gaitController.GetSerovAngles());
}
void Hexapod::SetGait(logic::gait::GaitType gaitType) {
    gaitController.ChangeGait(gaitType);
}
void Hexapod::SetSpeed(float speed) {
    gaitController.ChangeSpeed(speed);
}
void Hexapod::SetDirection(logic::GaitController::Direction direction) {
    gaitController.ChangeDirection(direction);
}

void Hexapod::CalibrateServos(const std::array<int16_t, 12>& calibrationValues) {
    driver.CalibrateServos(calibrationValues);
}