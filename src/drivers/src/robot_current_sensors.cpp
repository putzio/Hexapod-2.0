#include "robot_current_sensors.hpp"

namespace pico_drivers {

    RobotCurrentSensors::RobotCurrentSensors(const std::array<uint8_t, 12> currentSensorsChannels, spi_inst_t* spi, uint32_t baudRate,
        uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t cs0Pin, uint8_t cs1Pin)
        :currentSensorsChannels(currentSensorsChannels),
        extern_adc({
                MCP3008(spi, baudRate, sckPin, txPin, rxPin, cs0Pin),
                MCP3008(spi, baudRate, sckPin, txPin, rxPin, cs1Pin)
            }) {
        for (std::vector<uint16_t>& sensor : currentSensorsBuffer) {
            sensor.resize(BUFFER_SIZE);
        }
        FillCurrentSensorsBuffer_blocking();
    }

    Result RobotCurrentSensors::ReadNextPairOfCurrentSensors() {
        Result result = Result::RESULT_OK;
        channelsReadIndex++;
        if (channelsReadIndex >= currentSensorsChannels.size() / 2) {
            buffer_index++;
            channelsReadIndex = 0;
            result = Result::RESULT_ALL_ADC_CHANNELS_READ_FINISHED;
        }
        if (buffer_index >= BUFFER_SIZE) {
            buffer_index = 0;
        }
        currentSensorsBuffer[channelsReadIndex][buffer_index] = extern_adc[0].ReadChannel(currentSensorsChannels[channelsReadIndex]);
        currentSensorsBuffer[channelsReadIndex + 6][buffer_index] = extern_adc[0].ReadChannel(currentSensorsChannels[channelsReadIndex + 6]);
        return result;
    }

    std::array<uint16_t, 12> RobotCurrentSensors::CalculateRMS() {
        for (int i = 0; i < currentSensorsBuffer.size(); i++) {
            uint32_t sum = 0;
            for (int j = 0; j < currentSensorsBuffer[i].size(); j++) {
                sum += currentSensorsBuffer[i][j] * currentSensorsBuffer[i][j];
            }
            currentSensorsRms[i] = sqrt(sum / currentSensorsBuffer[i].size());
        }
        return currentSensorsRms;
    }
    Result RobotCurrentSensors::FillCurrentSensorsBuffer_blocking() {
        Result result = Result::RESULT_OK;
        for (int i = 0; i < BUFFER_SIZE * 6; i++) {
            ReadNextPairOfCurrentSensors();
            sleep_ms(20);
        }
        return result;
    }
}