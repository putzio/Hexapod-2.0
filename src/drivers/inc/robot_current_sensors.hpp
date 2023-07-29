#pragma once
#include "mcp3008.hpp"
#include "Results.h"
#include <array>
#include "pinout.hpp"
#include "math.h"

namespace pico_drivers {
    class RobotCurrentSensors {
    public:
        RobotCurrentSensors(const std::array<uint8_t, 12> current_sensors_channels, spi_inst_t* spi, uint32_t baudRate,
            uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t cs0Pin, uint8_t cs1Pin);
        std::array<uint16_t, 12>  PeriodicProcess();
        std::array<uint16_t, 12> GetCurrentSensorRMS() { return current_sensors_rms; };
    private:
        Result ReadCurrentSensors();
        Result CalculateRMS();
        Result FillCurrentSensorsBuffer();
        const uint8_t BUFFER_SIZE = 20;
        uint8_t buffer_index = 0;
        std::array<MCP3008, 2> extern_adc;
        std::array<uint16_t, 12> current_sensors_rms;
        std::array<std::array<uint16_t, 20>, 12> current_sensors_buffer = { 0 };
        const std::array<uint8_t, 12> current_sensors_channels;
    };
}