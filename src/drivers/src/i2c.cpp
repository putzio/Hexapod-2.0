#include "i2c.hpp"

namespace pico_drivers {
    I2C::I2C(i2c_inst_t* i2c_instance, uint32_t baudRate, uint8_t i2cPins[2]) {
        m_i2c_instance = i2c_instance;
        i2c_init(m_i2c_instance, baudRate);
        gpio_set_function(i2cPins[0], GPIO_FUNC_I2C);
        gpio_set_function(i2cPins[1], GPIO_FUNC_I2C);
        gpio_pull_up(i2cPins[0]);
        gpio_pull_up(i2cPins[1]);
    };

    uint8_t I2C::Read(uint8_t adress, uint8_t* dataBufferPtr, size_t numberOfbytes, bool noStop, absolute_time_t maxBlockingTime_us) {
        return i2c_read_timeout_us(m_i2c_instance, adress, dataBufferPtr, numberOfbytes, noStop, maxBlockingTime_us);
    }

    uint8_t I2C::Write(uint8_t adress, uint8_t* dataBufferPtr, size_t numberOfbytes, bool noStop, absolute_time_t maxBlockingTime_us) {
        return i2c_write_timeout_us(m_i2c_instance, adress, dataBufferPtr, numberOfbytes, noStop, maxBlockingTime_us);
    }
}