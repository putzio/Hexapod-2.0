#include "gpio.hpp"

namespace pico_drivers {
    Gpio::Gpio(uint16_t pin, PinMode pinMode) {

        m_pin = pin;
        m_mode = pinMode;
        gpio_init(pin);
        gpio_set_dir(pin, (m_mode == OUTPUT));//true -> OUTPUT, false -> input
        if (m_mode == PULLDOWN) {
            gpio_pull_down(m_pin);
        }
        else if (m_mode == PULLUP) {
            gpio_pull_up(m_pin);
        }
    }

    void Gpio::Write(bool value) {
        if (m_mode == OUTPUT) {
            gpio_put(m_pin, value);
        }
    }

    bool Gpio::Read() {
        return gpio_get(m_pin);
    }

    void Gpio::Toggle() {
        Write(!gpio_get(m_pin));
    }
}