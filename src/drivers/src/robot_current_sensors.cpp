#include "robot_current_sensors.hpp"

namespace pico_drivers {

    RobotCurrentSensors::RobotCurrentSensors(const std::array<uint8_t, 12> current_sensors_channels, spi_inst_t* spi, uint32_t baudRate,
        uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t cs0Pin, uint8_t cs1Pin)
        :current_sensors_channels(current_sensors_channels),
        extern_adc({
                MCP3008(spi, baudRate, sckPin, txPin, rxPin, cs0Pin),
                MCP3008(spi, baudRate, sckPin, txPin, rxPin, cs1Pin)
            }) {
        // extern_adc[0] = MCP3008(SPI_INSTANCE, SPI_BAUD_RATE, SPI_CLK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_ADC0_PIN);
        // extern_adc[1] = MCP3008(SPI_INSTANCE, SPI_BAUD_RATE, SPI_CLK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_ADC0_PIN);
        FillCurrentSensorsBuffer();
    }
    std::array<uint16_t, 12> RobotCurrentSensors::PeriodicProcess() {
        ReadCurrentSensors();
        CalculateRMS();
        return current_sensors_rms;
    }

    Result RobotCurrentSensors::ReadCurrentSensors() {
        Result result = Result::RESULT_OK;
        if (buffer_index >= BUFFER_SIZE) {
            buffer_index = 0;
        }
        for (int i = 0; i < current_sensors_buffer.size(); i++) {
            current_sensors_buffer[i][buffer_index] = extern_adc[i / 6].ReadChannel(current_sensors_channels[i]);
        }
        buffer_index++;
        return result;
    }
    Result RobotCurrentSensors::CalculateRMS() {
        Result result = Result::RESULT_OK;
        for (int i = 0; i < current_sensors_buffer.size(); i++) {
            uint32_t sum = 0;
            for (int j = 0; j < current_sensors_buffer[i].size(); j++) {
                sum += current_sensors_buffer[i][j] * current_sensors_buffer[i][j];
            }
            current_sensors_rms[i] = sqrt(sum / current_sensors_buffer[i].size());
        }
        return result;
    }
    Result RobotCurrentSensors::FillCurrentSensorsBuffer() {
        Result result = Result::RESULT_OK;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            for (int j = 0; j < current_sensors_buffer.size(); j++) {
                current_sensors_buffer[j][i] = extern_adc[j / 6].ReadChannel(current_sensors_channels[j]);
            }
            sleep_ms(5);
        }
        return result;
    }
}