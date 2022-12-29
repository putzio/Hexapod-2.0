#pragma once

#include "Logic/Body.hpp"
#include "drivers/pwm_driver.hpp"

class BodyDriver:public Body
{
    private:
    Pwm_driver* drivers[12];
    public:
    BodyDriver(uint8_t pins [12]);
    
    void PassCalculatedValuesToMotors();
    
    void EnableMotors();
    void DisableMotors();
    
};
