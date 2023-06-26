#include <stdio.h>
#include <memory>
#include "pico/stdlib.h"
#include "pico/double.h"
#include "gpio.hpp"
#include "Servo.hpp"
#include "servo_left.hpp"

void UpdateServoDriver(std::shared_ptr<pico_drivers::Servo_Interface> servo, float angle) {
	servo->SetRadianAngle(angle);
}
Result ServoPeriodicProcess(std::shared_ptr<pico_drivers::Servo_Interface> servo_driver, logic::leg::Servo* servo) {
	Result r = servo->GoToTargetAngle();
	UpdateServoDriver(servo_driver, servo->GetCurrentAngle());
	return r;
}
int main() {
	stdio_init_all();
	pico_drivers::Gpio gpio = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
	logic::leg::Servo servo = logic::leg::Servo(1.570796371f);
	std::shared_ptr<pico_drivers::Servo_Interface> servo_driver = std::make_shared<pico_drivers::ServoLeft>(2);

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