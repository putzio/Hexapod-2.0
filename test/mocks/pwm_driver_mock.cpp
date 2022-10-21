#include "pwm_driver_mock.hpp"

void Pwm_driver::SetPwm(uint16_t value)
{
    this->currentPosition = value;
}

Pwm_driver::Pwm_driver(uint8_t pin)
{
    if(pin<20 && pin >= 0){
        this->pin = pin;
        InitPwm();
    }
}

void Pwm_driver::InitPwm()
{

}

uint8_t Pwm_driver::GetPin() {
    return pin;
}

void Pwm_driver::Enable()
{
    // Set the PWM running
    this->enabled = true;
}

void Pwm_driver::Disable()
{
    // Reset the PWM
    this->enabled = false;
}