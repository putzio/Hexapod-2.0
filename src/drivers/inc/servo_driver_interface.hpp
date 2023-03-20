#pragma once

#include "..\..\..\include\constants.hpp"
#include "pwm_driver.hpp"


class Servo_DriverInterface {
protected:
    int16_t calibrationValue;
    Pwm_driver* pwmDriver;
    uint16_t MapAngleToPwmTime(uint8_t angle);
public:
    virtual void SetAngle(uint8_t angle);
    virtual void SetRadianAngle(float angle);
    void Calibrate(int16_t value);
    virtual void Disable();
};