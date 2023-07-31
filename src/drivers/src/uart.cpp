#include "uart.hpp"

namespace pico_drivers {
    Uart::Uart(uart_inst_t* uartId, uint32_t baudRate, uint8_t txPin, uint8_t rxPin) {
        m_uartId = uartId;
        // m_baudRate = baudRate;
        // Set up our UART with the required speed.
        uart_init(uartId, baudRate);

        // Set the TX and RX pins by using the function select on the GPIO
        // Set datasheet for more information on function select
        gpio_set_function(txPin, GPIO_FUNC_UART);
        gpio_set_function(rxPin, GPIO_FUNC_UART);
    }
    void Uart::SendData(const std::string& data) {
        uart_puts(m_uartId, data.c_str());
        // for (char c : data) {
        //     uart_putc(m_uartId, c);
        // }
    }
}