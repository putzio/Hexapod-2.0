#include "gpio.hpp"

int main() {
    stdio_init_all();
    using namespace pico_drivers;
    Gpio driver = Gpio(PICO_DEFAULT_LED_PIN, Gpio::OUTPUT);
    while (1) {
        driver.Toggle();
        sleep_ms(1000);
    }
}
