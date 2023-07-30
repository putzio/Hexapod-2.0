#pragma once 

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

namespace web {
    struct Gpio_w {

        uint16_t m_pin;
        Gpio_w(uint16_t pin = CYW43_WL_GPIO_LED_PIN);

        void Write(bool value);
        void Toggle();
    };
}