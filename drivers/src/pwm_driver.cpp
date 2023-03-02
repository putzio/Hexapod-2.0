#include "../inc/pwm_driver.hpp"


void Pwm_driver::SetPwm(uint16_t value) {
    pwm_set_chan_level(this->slice_num, pwm_gpio_to_channel(this->pin), value);// + calibrationValue);
}
// void Pwm_driver::SetPwmForAngle(uint16_t angle) {
//     uint16_t pwmValue = angle / 180 * (Constants::ANGLE_RANGE_MS[1] - Constants::ANGLE_RANGE_MS[0]) + Constants::ANGLE_RANGE_MS[0];
//     SetPwm(pwmValue);
// }

Pwm_driver::Pwm_driver(uint8_t pin, uint16_t topCounterValue, uint8_t integerPrescaler_8b, uint8_t fractionalPrescaler_4b) {
    this->pin = pin;
    Initialize(topCounterValue, integerPrescaler_8b, fractionalPrescaler_4b);
}

void Pwm_driver::Initialize(uint16_t topCounterValue, uint8_t integerPrescaler_8b, uint8_t fractionalPrescaler_4b) {
    // Tell GPIO it is allocated to the PWM
    gpio_set_function(this->pin, GPIO_FUNC_PWM);
    // Find out which PWM slice is connected to GPIO
    this->slice_num = pwm_gpio_to_slice_num(this->pin);
    // Set period of 20000 cycles (0 to 20000 inclusive)
    pwm_set_wrap(this->slice_num, topCounterValue);
    // setting period = 20ms
    // set clk div to 38
    pwm_set_clkdiv_int_frac(this->slice_num, integerPrescaler_8b, fractionalPrescaler_4b);
}
// void Pwm_driver::Calibrate(uint16_t value) {
//     calibrationValue = value;
// }

uint8_t Pwm_driver::GetPin() {
    return pin;
}

void Pwm_driver::Enable() {
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
}

void Pwm_driver::Disable() {
    // Reset the PWM
    pwm_set_enabled(slice_num, false);
}