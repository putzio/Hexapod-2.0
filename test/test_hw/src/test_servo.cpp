#include "../inc/test_servo.hpp"

void test_servo_loop(std::shared_ptr<Servo_DriverInterface> driver, uint16_t* counter) {
    if (*counter < 90) {
        *counter = 90;
    }
    (*counter)++;
    if (*counter > 150) {
        *counter = 90;
    }
    driver->SetAngle(*counter);
}