#pragma once

#include "gaitController.hpp"
#include "uart.hpp"
#include "pinout.hpp"
#include "legs_controller.hpp"
#include "robot_current_sensors.hpp"
#include <unordered_map>
#include <string>
#include <time.h>
#include <array>

namespace pd = pico_drivers;
class Hexapod {
public:
    Hexapod();
    void PeriodicProcess();
    void SetGait(logic::gait::GaitType gaitType);
    void SetSpeed(float speed);
    void SetDirection(logic::GaitController::Direction direction);
    void CalibrateServos(const std::array<int16_t, 12>& calibrationValues);
    clock_t GetTime();

private:
    void UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges);
    void PrintDataInTeleplotFormat(std::array<uint16_t, 12> sensorData);
    pd::RobotCurrentSensors current_sensors;
    pd::LegsController legsController;
    logic::GaitController gaitController;
    uint8_t counter = 0;
    pd::Uart uart = pd::Uart(UART_ID, UART_BAUD_RATE, UART_TX_PIN, UART_RX_PIN);
    // struct repeating_timer servo_timer;
    struct repeating_timer adc_timer;
    std::unordered_map<std::string, uint16_t> maxTime = {
        {"Read_Current_Sensor", 20},
        {"Update_Servos", 25000}
    };
    std::unordered_map<std::string, clock_t> previousCallTime = {
        {"Read_Current_Sensors", 0},
        {"Update_Servos", 0}
    };
    const std::array<uint8_t, 12> currentSensorsChannels = { 7, 6, 4, 3, 1, 0, 1, 0, 3, 4, 6, 7 };
    uint16_t currentSensorChannelIndex = 0;
};