#include "../inc/test_servo.hpp"

std::shared_ptr<ServoDriverLeft> test_servo_setup(uint8_t pin) {
    // stdio_init_all;
}
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