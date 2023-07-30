#pragma once

//LIBRARIES
#include "robot_driver.hpp"
#include "gaitController.hpp"

class Hexapod {
public:
    void PeriodicProcess();
    void SetGait(logic::gait::GaitType gaitType);
    void SetSpeed(float speed);
    void SetDirection(logic::GaitController::Direction direction);
    void CalibrateServos(const std::array<int16_t, 12>& calibrationValues);

private:
    pico_drivers::RobotDriver driver;
    logic::GaitController gaitController;
};