#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "pinout.hpp"
#include <string>

namespace pico_drivers {
    class Uart {
    public:
        Uart(uart_inst_t* uartId, uint32_t baudRate, uint8_t txPin, uint8_t rxPin);
        void SendData(const std::string& data);
    private:
        uart_inst_t* m_uartId;
        // uint32_t m_baudRate;
    };
}

