#pragma once
#include "../../include/constants.hpp"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/double.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

class Pwm_driver {
protected:
    bool enabled;
    uint8_t pin;       // given by the user in the constructor
    uint16_t slice_num;    // defined in ServoInit() method form the pin variable
    void Initialize(uint16_t topCounterValue, uint8_t integerPrescaler_8b, uint8_t fractionalPrescaler_4b);
public:
    Pwm_driver(uint8_t pin, uint16_t topCounterValue = 20000, uint8_t integerPrescaler_8b = 125, uint8_t fractionalPrescaler_4b = 9);
    void SetPwm(uint16_t value);
    // void SetPwmForAngle(uint16_t angle);
    uint8_t GetPin();
    // void Calibrate(uint16_t value);
    void Enable();
    void Disable();
};