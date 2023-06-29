#include "mcp3008.hpp"
#include "gpio.hpp"
#include <array>

#define SPI_INSTANCE spi0
#define BAUD_RATE 250000
#define SCK_PIN 2
#define TX_PIN 3
#define RX_PIN 4
#define CS_PIN 5

void UpdateADC(std::array<uint16_t, 8> &adc_values, pico_drivers::MCP3008 &adc_spi_0);
void PrintADC(const std::array<uint16_t, 8> const& adc_values);

int main() {
    stdio_init_all();
    using namespace pico_drivers;
    Gpio gpio = Gpio(25, Gpio::OUTPUT);
    MCP3008 adc_spi_0 = MCP3008(SPI_INSTANCE, BAUD_RATE, SCK_PIN, TX_PIN, RX_PIN, CS_PIN);
    std::array<uint16_t, 8> adc_values;
    
    while (1) {
        UpdateADC(adc_values, adc_spi_0);
        PrintADC(adc_values);
        gpio.Toggle();
        sleep_ms(1000);
    }
}

void UpdateADC(std::array<uint16_t, 8>& adc_values, pico_drivers::MCP3008& adc_spi_0) {
    for (int i = 0; i < adc_values.size(); i++) {
        adc_values[i] = adc_spi_0.ReadChannel(i);
    }
}
void PrintADC(const std::array<uint16_t, 8> const& adc_values) {
    for (int i = 0; i < adc_values.size(); i++) {
        printf("ADC %d value: %d\n", i, adc_values[i]);
    }
}