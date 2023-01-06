#pragma once
#include <stdio.h>

class Pwm_driver
{
protected:
    bool enabled;
    uint8_t pin;       // given by the user in the constructor
    uint16_t slice_num;    // defined in ServoInit() method form the pin variable
    uint16_t calibrationValue;
public:
    Pwm_driver(uint8_t pin);
    void InitPwm();
    void SetPwm(uint16_t value);
    uint8_t GetPin();
    void Calibrate(uint16_t value);
    void Enable();
    void Disable();
};