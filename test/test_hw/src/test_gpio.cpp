#include "../inc/test_gpio.hpp"

void test_gpio(uint8_t pin) {
    stdio_init_all();
    Gpio_driver driver = Gpio_driver(pin, Gpio_driver::OUTPUT);
    while (1) {
        driver.Toggle();
        sleep_ms(1000);
    }
}