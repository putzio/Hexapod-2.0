#include "gpio_w.hpp"

namespace pico_drivers {
    Gpio_w::Gpio_w(uint16_t pin) {
        // cyw43_arch_init();
        m_pin = pin;
    }

    void Gpio_w::Write(bool value) {
        cyw43_arch_gpio_put(m_pin, value);
    }

    void Gpio_w::Toggle() {
        Write(!cyw43_arch_gpio_get(m_pin));
    }
}