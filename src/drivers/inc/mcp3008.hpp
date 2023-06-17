#pragma once
#include "spi.hpp"


namespace pico_drivers {
    class MCP3008 : public SPI {
    public:
        MCP3008(spi_inst_t* spi, uint32_t baudRate,
            uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t csPin,
            uint8_t data_bits, spi_cpol_t clockPolarity, spi_cpha_t clockPhase, spi_order_t dataOrder) :
            SPI(spi, baudRate, rxPin, txPin, sckPin, csPin, data_bits, clockPolarity, clockPhase, dataOrder) {
        }

        uint16_t ReadChannel(uint8_t channel);
    };
}