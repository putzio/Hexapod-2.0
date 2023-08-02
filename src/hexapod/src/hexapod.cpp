#include "hexapod.hpp"

Hexapod::Hexapod() :current_sensors(currentSensorsChannels,
    SPI_INSTANCE,
    SPI_BAUD_RATE,
    SPI_CLK_PIN,
    SPI_MOSI_PIN,
    SPI_MISO_PIN,
    SPI_CS_ADC0_PIN,
    SPI_CS_ADC1_PIN) {
    std::array<uint8_t, 12> pins;
    for (int i; i < pins.size(); i++) {
        pins[i] = i + FIRST_SERVO_PIN;
    }
    // legsController = pd::LegsController(pins);
    // add_repeating_timer_ms(5, GetCurrentSensorCallback(), &this->current_sensors, &adc_timer);
}

void Hexapod::PeriodicProcess() {
    if (previousCallTime["Read_Current_Sensor"] + maxTime["Read_CurrentSensor"] < GetTime()) {
        if (current_sensors.ReadNextPairOfCurrentSensors() ==
            Result::RESULT_ALL_ADC_CHANNELS_READ_FINISHED) {
            PrintDataInTeleplotFormat(current_sensors.CalculateRMS());
            // std::string data = ">step:" + std::to_string(gaitController.p_ptr_gaitInterface->step) + "\n";
            // uart.SendData(data.data());
        }
        previousCallTime["Read_Current_Sensors"] = GetTime();
    }
    if (previousCallTime["Update_Servos"] + maxTime["Update_Servos"] < GetTime()) {
        // gaitController.PeriodicProcess();
        // UpdateServos(gaitController.GetSerovAngles());
        previousCallTime["Update_Servos"] = GetTime();
    };
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
    // for (int i = 0; i < calibrationValues.size(); i++) {
    //     legsController.CalibrateServo(i, calibrationValues[i]);
    // }
    // legsController.InitServos();
}

void Hexapod::UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges) {
    // legsController.UpdateServos(newAnges);
}

clock_t Hexapod::GetTime() {
    return (clock_t)time_us_64();
}

void Hexapod::PrintDataInTeleplotFormat(std::array<uint16_t, 12> sensorData) {
    for (int i = 0; i < sensorData.size(); i++) {
        std::string data = ">s" + std::to_string(i) + ":" + std::to_string(sensorData[i]) + "\n";
        uart.SendData(data.c_str());
        printf(data.c_str());
    }
}