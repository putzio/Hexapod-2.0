#include "mcp3008.hpp"
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

void UpdateADC(std::array<uint16_t, 8>& adc_values, pico_drivers::MCP3008& adc_spi_0);
void PrintADC(const std::array<uint16_t, 8>& adc_values);

int main() {
    stdio_init_all();
    using namespace pico_drivers;
    Gpio led = Gpio(25, Gpio::OUTPUT);
    Gpio cs1 = Gpio(SPI_CS_ADC1_PIN, Gpio::OUTPUT);
    Gpio cs2 = Gpio(SPI_CS_FLASH_PIN, Gpio::OUTPUT);
    cs1.Write(1);
    cs2.Write(1);
    MCP3008 adc_spi_0 = MCP3008(SPI, BAUD_RATE, SCK_PIN, TX_PIN, RX_PIN, CS_PIN);
    std::array<uint16_t, 8> adc_values;
    clock_t adcPreviousCallTime = 0;
    clock_t ledPreviousCallTime = 0;
    while (1) {
        if (time_us_64() - adcPreviousCallTime > 10000) {
            UpdateADC(adc_values, adc_spi_0);
            adcPreviousCallTime = time_us_64();
        }
        if (time_us_64() - ledPreviousCallTime > 100000) {
            led.Toggle();
            ledPreviousCallTime = time_us_64();
        }
        // gpio.Toggle();
        // led.Toggle();
        sleep_ms(1);
    }
}

void UpdateADC(std::array<uint16_t, 8>& adc_values, pico_drivers::MCP3008& adc_spi_0) {
    for (int i = 0; i < adc_values.size(); i++) {
        adc_values[i] = adc_spi_0.ReadChannel(i);
    }
    PrintADC(adc_values);
}
void PrintADC(const std::array<uint16_t, 8>& adc_values) {
    for (int i = 0; i < adc_values.size(); i++) {
        printf(">ADC %d: %d\n", i, adc_values[i]);
    }
    printf(">Timestamp: %d\n", time_us_64());
    // for (int i = 0; i < adc_values.size(); i++) {
    //     std::string data = ">s" + std::to_string(i) + ":" + std::to_string(adc_values[i]) + "\n";
    //     printf(data.c_str());
    // }
}