#include "uart.hpp"
#include <stdio.h>
#include "pico/stdlib.h"
int main() {
    stdio_init_all();
    pico_drivers::Uart uart = pico_drivers::Uart(uart0, 115200, 0, 1);
    std::string data = "Hello World!\n";
    uart.SendData(data);
    while (1) {
        uart.SendData(data);
        sleep_ms(1000);
    }
    return 0;
}

// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/uart.h"

// /// \tag::hello_uart[]

// #define UART_ID uart0
// #define BAUD_RATE 115200

// // We are using pins 0 and 1, but see the GPIO function select table in the
// // datasheet for information on which other pins can be used.
// #define UART_TX_PIN 0
// #define UART_RX_PIN 1

// int main() {
//     // Set up our UART with the required speed.
//     uart_init(UART_ID, BAUD_RATE);

//     // Set the TX and RX pins by using the function select on the GPIO
//     // Set datasheet for more information on function select
//     gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
//     gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

//     // Use some the various UART functions to send out data
//     // In a default system, printf will also output via the default UART
//     while (1) {
//         // Send out a character without any conversions
//         uart_putc_raw(UART_ID, 'A');

//         // Send out a character but do CR/LF conversions
//         uart_putc(UART_ID, 'B');

//         // Send out a string, with CR/LF conversions
//         uart_puts(UART_ID, " Hello, UART!\n");
//         sleep_ms(1000);
//     }
// }