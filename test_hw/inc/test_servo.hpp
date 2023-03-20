#pragma once
#include "../../../drivers/inc/servo_driver_left.hpp"
#include <memory>

std::shared_ptr<ServoDriverLeft> test_servo_setup(uint8_t pin);
void test_servo_loop(std::shared_ptr<Servo_DriverInterface> driver, uint16_t* counter);