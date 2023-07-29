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

private:
    pico_drivers::RobotDriver driver;
    logic::GaitController gaitController;
};