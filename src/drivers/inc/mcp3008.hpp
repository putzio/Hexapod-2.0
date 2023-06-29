#pragma once
#include "spi.hpp"

namespace pico_drivers {
    class MCP3008 : public SPI {
    public:
        /**
         * @brief Construct a new MCP3008 object
         *
         * @param spi SPI instance (spi0 or spi1)
         * @param baudRate SPI baud rate
         * @param sckPin SPI clock PIN
         * @param txPin SPI MOSI PIN
         * @param rxPin SPI MISO PIN
         * @param csPin SPI chip select PIN
         */
        MCP3008(spi_inst_t* spi, uint32_t baudRate,
            uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t csPin) :
            SPI(spi, baudRate, rxPin, txPin, sckPin, csPin, data_bits, clockPolarity, clockPhase, dataOrder) {
        }

        uint16_t ReadChannel(uint8_t channel);

    private:
        uint8_t data_bits = 8;
        spi_cpol_t clockPolarity = SPI_CPOL_0;
        spi_cpha_t clockPhase = SPI_CPHA_0;
        spi_order_t dataOrder = SPI_MSB_FIRST;

    };
}