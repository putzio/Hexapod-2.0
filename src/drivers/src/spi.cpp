#include "spi.hpp"

namespace pico_drivers {
    SPI::SPI(spi_inst_t* spi, uint32_t baudRate,
        uint8_t rxPin, uint8_t txPin, uint8_t sckPin, uint16_t csPin,
        uint8_t data_bits, spi_cpol_t clockPolarity, spi_cpha_t clockPhase, spi_order_t dataOrder) {
        gpio_cs = new Gpio(csPin, Gpio::OUTPUT);
        gpio_cs->Write(1);

        spi_init(spi, baudRate);
        spi_set_format(spi, data_bits, clockPolarity, clockPhase, dataOrder);

        gpio_set_function(rxPin, GPIO_FUNC_SPI);
        gpio_set_function(txPin, GPIO_FUNC_SPI);
        gpio_set_function(sckPin, GPIO_FUNC_SPI);
        // gpio_set_function(csPin, GPIO_FUNC_SPI);
        this->spi = spi;
    }
    void SPI::SpiWrite(uint8_t* data, uint8_t size) {
        spi_write_blocking(spi, data, size);
    }
    void SPI::SpiRead(uint8_t repeated_tx_data, uint8_t* data, uint8_t size) {
        spi_read_blocking(spi, repeated_tx_data, data, size);
    }
    void SPI::SpiWriteRead(uint8_t* tx_data, uint8_t* rx_data, uint8_t size) {
        printf("Number of bytes read: %d\n", spi_write_read_blocking(spi, tx_data, rx_data, size));
    };
}