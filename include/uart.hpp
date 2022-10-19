#pragma once
#include "pico/stdlib.h"
#include "config.h"

void InitUart(uart_inst_t *uart = UART_ID, uint baudrate = BAUD_RATE, 
        uint rx_pin = RX_PIN, uint tx_pin = TX_PIN);
void OnUartRx(); // bool *changeVelocity, *velocityChanged, *velocity, *mode
void InterruptControl(irq_handler_t handler = OnUartRx);