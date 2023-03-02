#include "./test_hw/inc/test_gpio.hpp"
#include "./test_hw/inc/test_pwm.hpp"
#include "./test_hw/inc/test_servo.hpp"
#include <memory>


int main() {
    // test_gpio(25);
    uint16_t pwmCounter, servoCounter = 100;
    stdio_init_all;
    std::shared_ptr<Pwm_driver> pwm = test_pwm_setup(25);

    for (int i = 0; i < 2000; i++) {
        test_pwm_loop(pwm, &pwmCounter);
    }
    std::shared_ptr<Servo_DriverInterface> servo = std::make_shared<ServoDriverLeft>(0);



    while (1) {
        test_pwm_loop(pwm, &pwmCounter);
        if (pwmCounter < 115) {
            test_servo_loop(servo, &servoCounter);
        }
    }
}