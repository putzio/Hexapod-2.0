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
        RobotCurrentSensors(const std::array<uint8_t, 12> current_sensors_channels, spi_inst_t* spi, uint32_t baudRate,
            uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t cs0Pin, uint8_t cs1Pin);
        std::array<uint16_t, 12> GetCurrentSensorRMS() { return currentSensorsRms; };
        Result ReadNextPairOfCurrentSensors();
        uint16_t GetBufferSize() { return BUFFER_SIZE; };
        std::array<uint16_t, 12> CalculateRMS();
    private:
        
        Result FillCurrentSensorsBuffer_blocking();
        const uint8_t BUFFER_SIZE = 100;
        uint8_t buffer_index = 0;
        std::array<MCP3008, 2> extern_adc;
        std::array<uint16_t, 12> currentSensorsRms;
        std::array<std::vector<uint16_t>, 12> currentSensorsBuffer;
        const std::array<uint8_t, 12> currentSensorsChannels;
        uint8_t channelsReadIndex = 0;
    };
}