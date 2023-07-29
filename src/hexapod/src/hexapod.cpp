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
// void Hexapod::SetSpeed(float speed){
//     gaitController.ChangeSpeed(speed);
// }
void Hexapod::SetDirection(logic::GaitController::Direction direction) {
    gaitController.ChangeDirection(direction);
}

// int main() {
//     stdio_init_all();
//     pico_drivers::Gpio led = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
//     led.Write(true);
//     std::array<uint8_t, 12> pins;
//     for (int i; i < pins.size(); i++) {
//         pins[i] = i + FIRST_SERVO_PIN;
//     }
//     pico_drivers::LegsController legsController = pico_drivers::LegsController(pins);
//     legsController.InitServos();
//     logic::GaitController gaitController = logic::GaitController();

//     gaitController.ChangeGait(logic::gait::GaitInterface::CATERPILLAR);
//     gaitController.ChangeDirection(logic::GaitController::FOREWARD);
//     gaitController.ResetLegTargetPositions();

//     legsController.UpdateServos(gaitController.GetSerovAngles());
//     sleep_ms(2000);
//     while (1) {
//         sleep_ms(50);
//         led.Toggle();
//         gaitController.PeriodicProcess();
//         legsController.UpdateServos(gaitController.GetSerovAngles());
//     }
// }