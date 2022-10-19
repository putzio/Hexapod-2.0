#include "uart.hpp"
#include "functions.h"
extern bool changeVelocity; 
extern bool velocityChanged; 
extern int velocity; 
extern enum Mode mode;

void InitUart(uart_inst_t *uart, uint baudrate, uint rx_pin, uint tx_pin)
{
    uart_init(uart, baudrate);
    // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
    gpio_set_function(rx_pin, GPIO_FUNC_UART);
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    InterruptControl();
}

void OnUartRx() // bool *changeVelocity, *velocityChanged, *velocity, *mode
{
    //----------getting the robot moves-----------------
    char recMode;
    while (uart_is_readable(UART_ID))
    {
        recMode = uart_getc(UART_ID);
        uart_puts(UART_ID, "Recieved:\n");
        uart_putc(UART_ID, recMode);
        uart_puts(UART_ID, "\n");
        if((recMode > (char)'A' && recMode < (char)'z') || recMode == '&')
            break;
    }        
    Message(changeVelocity, velocityChanged, velocity, mode, recMode);
}

void InterruptControl(irq_handler_t handler)
{
    // interrupts
    //  Set up a RX interrupt
    //  We need to set up the handler first
    //  Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, handler);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);
}