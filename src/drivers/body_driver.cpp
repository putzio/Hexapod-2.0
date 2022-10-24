#include "drivers/body_driver.hpp"

BodyDriver::BodyDriver(uint8_t pins[12]):Body()
{
    for(int i = 0; i < 12; i++)
    {
        drivers[i] =  new Pwm_driver(pins[i]);
    }
}

void BodyDriver::PassCalculatedValuesToMotors()
{
    for(int i = 0; i < 6; i++)
    {
        drivers[i]->SetPwm(legs[i].master.GetPwmValue());
        drivers[i+1]->SetPwm(legs[i].slave.GetPwmValue());
    }
}
    
void BodyDriver::EnableMotors()
{
    for(Pwm_driver* driver : drivers)
    {
        driver->Enable();
    }
}
void BodyDriver::DisableMotors()
{
    for(Pwm_driver* driver : drivers)
    {
        driver->Disable();
    }
}