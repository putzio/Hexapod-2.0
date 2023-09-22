#include "robot_current_sensors.hpp"
#include <stdio.h>

namespace pico_drivers {

    RobotCurrentSensors::RobotCurrentSensors(const std::array<uint8_t, 12>& currentSensorsChannels, spi_inst_t* spi, uint32_t baudRate,
        uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t cs0Pin, uint8_t cs1Pin)
        :currentSensorsChannels(currentSensorsChannels)
        // extern_adc({
        //         MCP3008(spi, baudRate, sckPin, txPin, rxPin, cs0Pin),
        //         MCP3008(spi, baudRate, sckPin, txPin, rxPin, cs1Pin)
        //     }) 
    {
        for (std::vector<uint16_t>& sensor : currentSensorsBuffer) {
            sensor.resize(BUFFER_SIZE);
        }
        // FillCurrentSensorsBuffer_blocking();
    }

    Result RobotCurrentSensors::UpdateCurrentSensors() {
        Result result = Result::RESULT_OK;
        buffer_index++;
        result = Result::RESULT_ALL_ADC_CHANNELS_READ_FINISHED;
        if (buffer_index >= BUFFER_SIZE) {
            buffer_index = 0;
        }
        for (int i = 0; i < currentSensorsChannels.size(); i++) {
            currentSensorsBuffer[i][buffer_index] = extern_adc[i / 6].ReadChannel(currentSensorsChannels[i]);
            if(i == 1){
                printf(">currentSensorsBuffer[%d][%d]: %d\n", i, buffer_index, currentSensorsBuffer[i][buffer_index]);
            }
        }
        return result;
    }

    // Result RobotCurrentSensors::UpdateCurrentSensors(std::array<bool, 6> groundDetectionEnabled) {
    //     Result result = Result::RESULT_OK;
    //     buffer_index++;
    //     result = Result::RESULT_ALL_ADC_CHANNELS_READ_FINISHED;
    //     if (buffer_index >= BUFFER_SIZE) {
    //         buffer_index = 0;
    //     }
    //     for (int i = 0; i < groundDetectionEnabled.size(); i++) {
    //         if(!groundDetectionEnabled[i]){
    //             continue;
    //         }
    //         currentSensorsBuffer[2 * i + 1][buffer_index] = extern_adc[i / 3].ReadChannel(currentSensorsChannels[2 * i + 1]);
    //     }
    //     return result;
    // }

    const std::array<float, 12>& RobotCurrentSensors::CalculateRMS() {
        for (int i = 0; i < currentSensorsBuffer.size(); i++) {
            uint32_t sum = 0;
            for (int j = 0; j < BUFFER_SIZE; j++) {
                sum += currentSensorsBuffer[i][j] * currentSensorsBuffer[i][j];
            }
            currentSensorsRms[i] = sqrt(sum / BUFFER_SIZE);
        }
        return currentSensorsRms;
    }

    // const std::array<float, 12>& RobotCurrentSensors::CalculateRMS(std::array<bool, 6> groundDetectionEnabled){
    //     for (int i = 0; i < groundDetectionEnabled.size(); i++) {
    //         if(!groundDetectionEnabled[i]){
    //             continue;
    //         }
    //         uint32_t sum = 0;
    //         for (int j = 0; j < BUFFER_SIZE; j++) {
    //             sum += currentSensorsBuffer[2 * i + 1][j] * currentSensorsBuffer[2 * i + 1][j];
    //         }
    //         currentSensorsRms[i] = sqrt(sum / BUFFER_SIZE);
    //     }
    //     return currentSensorsRms;
    // }

    Result RobotCurrentSensors::FillCurrentSensorsBuffer_blocking() {
        Result result = Result::RESULT_OK;
        for (int i = 0; i < BUFFER_SIZE * 6; i++) {
            UpdateCurrentSensors();
            sleep_ms(20);
        }
        return result;
    }
}