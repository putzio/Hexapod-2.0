#pragma once
#include "../../../drivers/inc/pwm_driver.hpp"
#include <memory>

std::shared_ptr<Pwm_driver> test_pwm_setup(uint8_t pin);
void test_pwm_loop(std::shared_ptr<Pwm_driver> driver, uint16_t* counter);