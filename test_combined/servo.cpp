#include <stdio.h>
#include <memory>
#include "pico/stdlib.h"
#include "pico/double.h"
#include "../drivers/inc/gpio_driver.hpp"
#include "../Logic/inc/Servo.hpp"
#include "../drivers/inc/servo_driver_left.hpp"

void UpdateServoDriver(std::shared_ptr<Servo_DriverInterface> servo_driver, float angle) {
    servo_driver->SetRadianAngle(angle);
}
Result ServoPeriodicProcess(std::shared_ptr<Servo_DriverInterface> servo_driver, Servo* servo) {
    Result r = servo->GoToTargetAngle();
    UpdateServoDriver(servo_driver, servo->GetCurrentAngle());
    return r;
}
int main() {
    stdio_init_all();
    Gpio_driver gpio = Gpio_driver(25, Gpio_driver::OUTPUT);
    Servo servo = Servo(1.570796371F);
    std::shared_ptr<Servo_DriverInterface> servo_driver = std::make_shared<ServoDriverLeft>(2);

    UpdateServoDriver(servo_driver, servo.GetCurrentAngle());
    servo.SetTargetAngle(110.0 / 180.0 * 3.14, Constants::PI / 180.0);
    while (1) {
        if (ServoPeriodicProcess(servo_driver, &servo) == RESULT_SERVO_IN_TARGET_POSITION) {
            if (servo.GetTargetAngle() > 105.0 / 180.0 * 3.14)
                servo.SetTargetAngle(100.0 / 180.0 * 3.14);
            else
                servo.SetTargetAngle(110.0 / 180.0 * 3.14);
        }
        gpio.Toggle();
        sleep_ms(100);
    }
}