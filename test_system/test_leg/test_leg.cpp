#include <stdio.h>
#include <memory>
#include "pico/stdlib.h"
#include "pico/double.h"
#include "gpio.hpp"
#include "Leg.hpp"
#include "servo_interface.hpp"
#include "servo_left.hpp"

void UpdateLeg(std::array<std::shared_ptr<pico_drivers::Servo_Interface>, 2> servo_drivers, logic::leg::ServosPositions angles) {
	servo_drivers[0]->SetRadianAngle(angles.upperServoAngle);
	servo_drivers[1]->SetRadianAngle(angles.lowerServoAngle);
}
Result LegPeriodicProcess(std::array<std::shared_ptr<pico_drivers::Servo_Interface>, 2> servo_drivers, logic::leg::Leg* leg) {
	Result r = leg->LegPeriodicProcess();
	UpdateLeg(servo_drivers, leg->p_servos.GetCurrentServoPositions());
	return r;
}
int main() {
	stdio_init_all();
	sleep_ms(5000);
	pico_drivers::Gpio gpio = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
	// Servo servo = Servo(1.570796371f);
	logic::leg::Leg leg = logic::leg::Leg(1.570796371f, 1.570796371f, logic::leg::Side::KNEE_BACK);
	std::array<std::shared_ptr<pico_drivers::Servo_Interface>, 2> servo_drivers = { std::make_shared<pico_drivers::ServoLeft>(2),
																				   std::make_shared<pico_drivers::ServoLeft>(3) };
	logic::leg::LegRange legRange;
	legRange = leg.GetRange();
	legRange.x[0] = 0;
	printf("X: %f \r\n", leg.GetFootCoordinates().x.GetCoordinate());
	printf("Y: %f \r\n", leg.GetFootCoordinates().y.GetCoordinate());
	printf("X: %f \r\n", leg.p_controller.GetX().GetCoordinate());
	printf("Y: %f \r\n", leg.p_controller.GetY().GetCoordinate());
	UpdateLeg(servo_drivers, leg.p_servos.GetCurrentServoPositions());
	logic::leg::FootTargetPosition footTargetPosition;
	footTargetPosition.x.SetCoordinate_mm(10);
	footTargetPosition.footOnGround = false;
	sleep_ms(2000);
	printf("Set New Target result: %d", leg.SetNewTargetPosition(footTargetPosition));

	while (1) {
		Result r = leg.LegPeriodicProcess();
		printf("Leg Periodic process result: %d\n", r);
		if (r == RESULT_LEG_IN_TARGET_POSITION) {
			if (footTargetPosition.x.GetCoordinate_mm() > 1.0f) {
				footTargetPosition.x.SetCoordinate_mm(legRange.x[0].GetCoordinate_mm());
				footTargetPosition.footOnGround = true;
			}
			else {
				footTargetPosition.x.SetCoordinate_mm(legRange.x[1].GetCoordinate_mm());
				footTargetPosition.footOnGround = false;
			}
			leg.SetNewTargetPosition(footTargetPosition);
		}
		printf("upper angle: %f \r\n", leg.p_servos.GetCurrentServoPositions().upperServoAngle);
		printf("lower angle: %f \r\n", leg.p_servos.GetCurrentServoPositions().lowerServoAngle);
		printf("target X: %f \r\n", leg.GetFootCoordinates().x.GetCoordinate());
		printf("target Y: %f \r\n", leg.GetFootCoordinates().y.GetCoordinate());

		printf("X: %f \r\n", leg.p_controller.GetX().GetCoordinate());
		printf("Changing step: %f \r\n", leg.GetChangingStep());
		gpio.Toggle();
		UpdateLeg(servo_drivers, leg.p_servos.GetCurrentServoPositions());
		sleep_ms(100);
	}
}