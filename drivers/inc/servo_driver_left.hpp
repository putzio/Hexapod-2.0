#pragma once

#include "pwm_driver.hpp"
#include "servo_driver_interface.hpp"

class ServoDriverLeft: public Servo_DriverInterface {
public:
    ServoDriverLeft(uint8_t newPin);
    void SetAngle(uint8_t angle) override;
    void Disable() override { pwmDriver->Disable(); };
    // void TestPWM() { SetPwm(10000); Enable(); }
};