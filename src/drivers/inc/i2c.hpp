#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"

namespace pico_drivers {
    class I2C {
        i2c_inst_t* m_i2c_instance;

    public:
        I2C(i2c_inst_t* i2c_instance, uint32_t baudRate, uint8_t i2cPins[2]);

        uint8_t Read(uint8_t adress, uint8_t* dataBufferPtr, size_t numberOfbytes, bool noStop, absolute_time_t maxBlockingTime_us);
        uint8_t Write(uint8_t adress, uint8_t* dataBufferPtr, size_t numberOfbytes, bool noStop, absolute_time_t maxBlockingTime_us);


    };
}