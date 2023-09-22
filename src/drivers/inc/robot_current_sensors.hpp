#pragma once
#include "mcp3008.hpp"
#include "Results.h"
#include <array>
#include "pinout.hpp"
#include "math.h"
#include "functional"
#include <vector>

namespace pico_drivers {
    class RobotCurrentSensors {
    public:
        RobotCurrentSensors(const std::array<uint8_t, 12>& current_sensors_channels, spi_inst_t* spi, uint32_t baudRate,
            uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t cs0Pin, uint8_t cs1Pin);
        const std::array<float, 12>& GetCurrentSensorRMS() { return currentSensorsRms; };
        Result UpdateCurrentSensors();
        // Result UpdateCurrentSensors(std::array<bool, 6> groundDetectionEnabled);
        uint16_t GetBufferSize() { return BUFFER_SIZE; };
        const std::array<float, 12>& CalculateRMS();
        // const std::array<float, 12>& CalculateRMS(std::array<bool, 6> groundDetectionEnabled);
        std::array<MCP3008, 2> extern_adc = {
                    MCP3008(SPI_INSTANCE, SPI_BAUD_RATE, SPI_CLK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_ADC0_PIN),
                    MCP3008(SPI_INSTANCE, SPI_BAUD_RATE, SPI_CLK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_ADC1_PIN)
        };
        std::array<std::vector<uint16_t>, 12> currentSensorsBuffer;
    private:

        Result FillCurrentSensorsBuffer_blocking();
        const uint8_t BUFFER_SIZE = 150;
        uint8_t buffer_index = 0;
        // std::array<MCP3008, 2> extern_adc;
        std::array<float, 12> currentSensorsRms;
        // std::array<std::vector<uint16_t>, 12> currentSensorsBuffer;
        const std::array<uint8_t, 12> currentSensorsChannels;
        uint8_t channelsReadIndex = 0;
    };
}