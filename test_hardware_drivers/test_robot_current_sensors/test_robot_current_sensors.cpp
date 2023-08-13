// #include "mcp3008.hpp"
#include "robot_current_sensors.hpp"
#include "gpio.hpp"
#include <array>
#include "pinout.hpp"
#include <string>
#include "hardware/timer.h"

#define SPI SPI_INSTANCE
#define BAUD_RATE SPI_BAUD_RATE
#define SCK_PIN SPI_CLK_PIN
#define TX_PIN  SPI_MOSI_PIN
#define RX_PIN SPI_MISO_PIN
#define CS_PIN SPI_CS_ADC0_PIN

using namespace pico_drivers;
void PrintADC(const std::array<float, 12>& adc_values);
clock_t GetTime() {
    return (clock_t)time_us_64() / 1000;
}

int main() {
    stdio_init_all();
    Gpio led = Gpio(25, Gpio::OUTPUT);
    // Gpio cs1 = Gpio(SPI_CS_ADC1_PIN, Gpio::OUTPUT);
    Gpio cs2 = Gpio(SPI_CS_FLASH_PIN, Gpio::OUTPUT);
    // cs1.Write(1);
    cs2.Write(1);
    const std::array<uint8_t, 12> currentSensorsChannels = { 1,2,3,4,7,6,7 };
    // MCP3008 adc_spi_0 = MCP3008(SPI, BAUD_RATE, SCK_PIN, TX_PIN, RX_PIN, CS_PIN);
    RobotCurrentSensors robotCurrentSensors = RobotCurrentSensors(currentSensorsChannels,
        SPI_INSTANCE,
        SPI_BAUD_RATE,
        SPI_CLK_PIN,
        SPI_MOSI_PIN,
        SPI_MISO_PIN,
        SPI_CS_ADC0_PIN,
        SPI_CS_ADC1_PIN);
    // MCP3008 adc_spi_0 = MCP3008(SPI, BAUD_RATE, SCK_PIN, TX_PIN, RX_PIN, CS_PIN);
    std::array<std::array<uint16_t, 8>, 2> adc_values;

    clock_t adc2PreviousCallTime = 0;
    clock_t adcPreviousCallTime = 0;

    while (1) {
        if (GetTime() - adcPreviousCallTime > 100) {
            // UpdateADC(adc_values[0], robotCurrentSensors_test.externAdc[0]);
            robotCurrentSensors.UpdateCurrentSensors();
            PrintADC(robotCurrentSensors.CalculateRMS());
            adcPreviousCallTime = GetTime();
            led.Toggle();
        }
        sleep_ms(20);
    }
}

void UpdateADC(std::array<float, 12>& adc_values, pico_drivers::MCP3008& adc_spi_0) {
    for (int i = 0; i < adc_values.size(); i++) {
        adc_values[i] = adc_spi_0.ReadChannel(i);
    }
}
void PrintADC(const std::array<float, 12>& adc_values) {
    for (int i = 0; i < adc_values.size(); i++) {
        printf(">ADC %d: %f\n", i, adc_values[i]);
    }
    printf(">Timestamp: %d\n", GetTime());
    // for (int i = 0; i < adc_values.size(); i++) {
    //     std::string data = ">s" + std::to_string(i) + ":" + std::to_string(adc_values[i]) + "\n";
    //     printf(data.c_str());
    // }
}