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
    legsController = pd::LegsController(pins);
    pico_drivers::Gpio cs2 = pico_drivers::Gpio(SPI_CS_FLASH_PIN, pico_drivers::Gpio::OUTPUT);
    cs2.Write(1);
    // add_repeating_timer_ms(5, GetCurrentSensorCallback(), &this->current_sensors, &adc_timer);
}

void Hexapod::AdcPeriodicProcess() {
    if (previousCallTime["Read_Current_Sensor"] + maxTime["Read_CurrentSensor"] < GetTime()) {
        if (current_sensors.UpdateCurrentSensors() ==
            Result::RESULT_ALL_ADC_CHANNELS_READ_FINISHED) {
            current_sensors.CalculateRMS();
            PrintDataInTeleplotFormat();
            // std::string data = ">step:" + std::to_string(gaitController.p_ptr_gaitInterface->step) + "\n";
            // uart.SendData(data.data());
        }
        previousCallTime["Read_Current_Sensors"] = GetTime();
    }
}
void Hexapod::GaitControllerPeriodicProcess() {
    if (previousCallTime["Update_Servos"] + maxTime["Update_Servos"] < GetTime()) {
        gaitController.PeriodicProcess();
        UpdateServos(gaitController.GetSerovAngles());
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
    if (previousCallTime["Update_Servos"] + maxTime["Update_Servos"] < GetTime()) {
        for (int i = 0; i < calibrationValues.size(); i++) {
            legsController.CalibrateServo(i, calibrationValues[i]);
        }
        gaitController.StandUp();
        UpdateServos(gaitController.GetSerovAngles());
        previousCallTime["Update_Servos"] = GetTime();
    }
}

void Hexapod::UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges) {
    legsController.UpdateServos(newAnges);
}

clock_t Hexapod::GetTime() {
    return (clock_t)time_us_64();
}

void Hexapod::PrintDataInTeleplotFormat() {
    std::array<float, 12> adcRms = current_sensors.GetCurrentSensorRMS();
    for (int i = 0; i < adcRms.size(); i++) {
        std::string data = ">s" + std::to_string(i) + ":" + std::to_string(adcRms[i]) + "\n";
        uart.SendData(data.c_str());
        printf(data.c_str());
    }
    std::string data = ">step:" + std::to_string(gaitController.p_ptr_gaitInterface->step) + "\n";
    uart.SendData(data.c_str());
}