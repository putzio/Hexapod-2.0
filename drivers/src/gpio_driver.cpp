#include "../inc/gpio_driver.hpp"

Gpio_driver::Gpio_driver(uint16_t pin, PinMode pinMode) {

    m_pin = pin;
    m_mode = pinMode;
    gpio_init(pin);
    gpio_set_dir(pin, (m_mode == OUTPUT));
    if (m_mode == PULLDOWN) {
        gpio_pull_down(m_pin);
    }
    else if (m_mode == PULLUP) {
        gpio_pull_up(m_pin);
    }
}

void Gpio_driver::Write(bool value) {
    if (m_mode == OUTPUT) {
        gpio_put(m_pin, value);
    }
}

bool Gpio_driver::Read() {
    gpio_get(m_pin);
}

void Gpio_driver::Toggle() {
    Write(!gpio_get(m_pin));
}