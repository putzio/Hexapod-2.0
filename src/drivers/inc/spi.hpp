#pragma once

#include <stdio.h>
#include "hardware/spi.h"
#include "gpio.hpp"


namespace pico_drivers {
    class SPI {
    protected:
        spi_inst_t* spi;
        Gpio* gpio_cs;
        SPI(spi_inst_t* spi, uint32_t baudRate,
            uint8_t rxPin, uint8_t txPin, uint8_t sckPin, uint16_t csPin,
            uint8_t data_bits, spi_cpol_t clockPolarity, spi_cpha_t clockPhase, spi_order_t dataOrder);
        ~SPI() {
            delete gpio_cs;
        };
        void SpiWrite(uint8_t* data, uint8_t size);
        void SpiRead(uint8_t repeated_tx_data, uint8_t* data, uint8_t size);
        void SpiWriteRead(uint8_t* tx_data, uint8_t* rx_data, uint8_t size);
    };
}