#pragma once

#include "gaitController.hpp"
#include "uart.hpp"
#include "pinout.hpp"
#include "legs_controller.hpp"
#include "robot_current_sensors.hpp"
#include <unordered_map>
#include <string>
#include "hardware/timer.h"
#include <array>
#include <queue>

namespace pd = pico_drivers;
class Hexapod {
public:
    Hexapod();
    void AdcPeriodicProcess();
    void GaitControllerPeriodicProcess();
    void SetGait(logic::gait::GaitType gaitType);
    void SetSpeed(float speed);
    void SetDirection(logic::GaitController::Direction direction);
    void CalibrateServos(const std::array<int16_t, 12>& calibrationValues);
    clock_t GetTime();
    clock_t GetTimeMs();
    logic::GaitController::Direction GetDirection() { return gaitController.direction; };
    bool IsGroundDetected(uint8_t legIndex);
    uint8_t legFalling = false;
    void SetLegGroundDetectionState(uint8_t leg, bool groundDetectionEnabled);
    void ResetGroundDetection(uint8_t leg);
    bool IsLegGroundDetected(uint8_t leg){return groundDetected[leg];};

private:
    void UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges);
    void PrintDataInTeleplotFormat();
    const std::array<uint8_t, 12> currentSensorsChannels = { 7, 6, 4, 3, 1, 0, 1, 0, 3, 4, 6, 7 };
    pd::RobotCurrentSensors current_sensors;
    pd::LegsController legsController;
    logic::GaitController gaitController;
    uint8_t counter = 0;
    pd::Uart uart = pd::Uart(UART_ID, UART_BAUD_RATE, UART_TX_PIN, UART_RX_PIN);
    std::unordered_map<std::string, uint16_t> maxTime = {
        {"Read_Current_Sensor", 50},
        {"Update_Servos", 25000}
    };
    std::unordered_map<std::string, uint64_t> previousCallTime = {
        {"Read_Current_Sensors", 0},
        {"Update_Servos", 0}
    };
    uint8_t currentSensorChannelIndex = 0;
    std::array<std::queue<float>, 6> currentSensorRmsQueue;
    const uint16_t CURRENT_SENSOR_RMS_QUEUE_SIZE = 15;// 150 ms / every 25 us = 6 // 25 us * 60 = 1.5 ms
    const uint8_t CURRENT_SENSOR_RMS_THRESHOLD = 10;
    std::array<bool, 6> groundDetected = { false, false, false, false, false, false };
};

    // Every 25 us new rms
    // window_time: 150us
    // lower_servo_threshold: 10