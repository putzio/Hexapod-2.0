#include "robot_driver.hpp"

namespace pico_drivers {
    RobotDriver::RobotDriver() :
        current_sensors(current_sensors_channels, SPI_INSTANCE, SPI_BAUD_RATE, SPI_CLK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_ADC0_PIN, SPI_CS_ADC1_PIN) {
        std::array<uint8_t, 12> pins;
        for (int i; i < pins.size(); i++) {
            pins[i] = i + FIRST_SERVO_PIN;
        }
        legsController = LegsController(pins);
    }
    std::array<uint16_t, 12> RobotDriver::UpdateCurrentSensorsValues() {
        return current_sensors.PeriodicProcess();
    };
    void RobotDriver::UpdateServos(std::array<logic::leg::ServosPositions, 6> newAnges) {
        legsController.UpdateServos(newAnges);
    };
}