
#include <stdio.h>
#include "leg.hpp"
#include "legs_controller.hpp"
#include "pinout.hpp"
#include "hardware/timer.h"

namespace l = logic::leg;
namespace pd = pico_drivers;

uint32_t previousCallTime = 0;
uint32_t maxTime = 100;

clock_t GetTime() {
    return (clock_t)time_us_64();
}

// void AdcPeriodicProcess() {
//     if (previousCallTime + maxTime < GetTime()) {
//         if (current_sensors.UpdateCurrentSensors() ==
//             Result::RESULT_ALL_ADC_CHANNELS_READ_FINISHED) {
//             current_sensors.CalculateRMS();
//             PrintDataInTeleplotFormat();
//             std::array<float, 12> adcRms = current_sensors.GetCurrentSensorRMS();
//             for (int i = 0; i < currentSensorRmsQueue.size(); i++) {
//                 currentSensorRmsQueue[i].push(adcRms[i] + adcRms[i + 6]);
//                 if (currentSensorRmsQueue[i].size() > CURRENT_SENSOR_RMS_QUEUE_SIZE) {
//                     currentSensorRmsQueue[i].pop();
//                 }
//             }

//             // std::string data = ">step:" + std::to_string(gaitController.p_ptr_gaitInterface->step) + "\n";
//             // uart.SendData(data.data());
//         }
//         previousCallTime = GetTime();
//     }
// }

int main() {
    stdio_init_all();
    std::array<uint8_t, 12> pins;
    for (int i; i < pins.size(); i++) {
        pins[i] = i + FIRST_SERVO_PIN;
    }
    pd::LegsController legsController = pd::LegsController(pins);
    legsController.InitServos();
    std::array<l::Leg, 6> legs;
    std::array<l::ServosPositions, 6> newAngles;



    while (1) {

    }
    return 0;
}
