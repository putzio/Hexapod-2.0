#pragma once 

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

namespace pico_drivers {
    struct pico_w_object {

        static bool cyw43_arch_initialised = false;
        pico_w_object();
        void InitialisePicoW(){
            if (!initialised) {
                stdio_init_all();
                cyw43_arch_init();
                initialised = true;
            }
        }
    };
}