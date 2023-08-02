#include "mcp3008.hpp"
#include "gpio.hpp"
#include <array>
#include "pinout.hpp"
#include <string>

#define SPI_INSTANCE spi0
#define BAUD_RATE 250000
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
    MCP3008 adc_spi_0 = MCP3008(SPI_INSTANCE, BAUD_RATE, SCK_PIN, TX_PIN, RX_PIN, CS_PIN);
    std::array<uint16_t, 8> adc_values;

    while (1) {
        UpdateADC(adc_values, adc_spi_0);
        PrintADC(adc_values);
        // gpio.Toggle();
        led.Toggle();
        sleep_ms(1000);
    }
}

void UpdateADC(std::array<uint16_t, 8>& adc_values, pico_drivers::MCP3008& adc_spi_0) {
    for (int i = 0; i < adc_values.size(); i++) {
        adc_values[i] = adc_spi_0.ReadChannel(i);
    }
}
void PrintADC(const std::array<uint16_t, 8>& adc_values) {
    for (int i = 0; i < adc_values.size(); i++) {
        printf("ADC %d value: %d\n", i, adc_values[i]);
    }
    for (int i = 0; i < adc_values.size(); i++) {
        std::string data = ">s" + std::to_string(i) + ":" + std::to_string(adc_values[i]) + "\n";
        printf(data.c_str());
    }
}