#pragma once
#include <stdio.h>
#include "BasicServo.hpp"

class Pwm_driver:BasicServo
{
protected:
    bool enabled;
    uint8_t pin;       // given by the user in the constructor
    uint16_t slice_num;    // defined in ServoInit() method form the pin variable
    uint16_t calibrationValue;
    void SetPwm(uint16_t value);
public:
    Pwm_driver(uint8_t pin);
    void InitPwm();
    uint8_t GetPin();
    void Enable();
    void Disable();
};