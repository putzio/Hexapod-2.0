#include "mcp3008.hpp"

namespace pico_drivers {
    uint16_t MCP3008::ReadChannel(uint8_t channel) {
        // Declare data that we will send
        uint8_t tx_data[3] = { 0 };
        tx_data[0] = ((0x01 << 7) |		// start bit
            (1 << 6) |			// SGL
            ((channel & 0x07) << 3)); 	// channel number
        tx_data[1] = 0x00;
        tx_data[2] = 0x00;
        // Data that we will get
        uint8_t rx_data[3] = { 0 };

        SpiWriteRead(tx_data, rx_data, 6);
        gpio_cs->Write(0);
        SpiWriteRead(tx_data, rx_data, 3);
        gpio_cs->Write(1);
        // Compute the ADC
        return 0x3FF & ((rx_data[0] & 0x01) << 9 | (rx_data[1] & 0xFF) << 1 | (rx_data[2] & 0x80) >> 7);
    }
}