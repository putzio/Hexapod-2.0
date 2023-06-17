#pragma once 

#include <stdio.h>
#include "pico/stdlib.h"

namespace pico_drivers {
    struct Gpio {
        typedef enum {
            INPUT,
            OUTPUT,
            PULLUP,
            PULLDOWN
        }PinMode;

        uint16_t m_pin;
        PinMode m_mode;
        Gpio(uint16_t pin, PinMode pinMode);

        void Write(bool value);
        void Toggle();
        bool Read();
    };
}