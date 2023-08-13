#include "gpio_w.hpp"

int main() {
    stdio_init_all();
    using namespace web;
    cyw43_arch_init();
    Gpio_w driver = Gpio_w();
    while (1) {
        driver.Toggle();
        sleep_ms(1000);
    }
}
