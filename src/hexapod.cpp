#include <stdio.h>
#include <memory>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/double.h"
#include "hardware/clocks.h"
// #include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "drivers/inc/gpio_driver.hpp"
#include "Logic/inc/Leg.hpp"
#include "drivers/inc/servo_driver_left.hpp"
// #include "Leg.hpp"
// #include "../Logic/inc/Body.hpp"
// #include "../include/uart.hpp"
// #include "../include/functions.h"
// #include "../include/enum_types.h"
// #include "../drivers/inc/pwm_driver.hpp"
// #include "../drivers/inc/gpio_driver.hpp"
// #include "../drivers/inc/servo_driver_left.hpp"
// #include "../drivers/inc/servo_driver_interface.hpp"

// const int16_t SERVO_CALIB[12] = {
//     155,
//     -60,
//     -155,
//     -80,
//     20,
//     95,
//     -30,
//     60,
//     55,
//     -70,
//     90,
//     -50};

// bool changeVelocity = false;
// int velocity = MIN_VELOCITY;
// bool velocityChanged = false;
// Mode mode = Pos90Mode;



int main() {
    stdio_init_all();
    Gpio_driver gpio = Gpio_driver(25, Gpio_driver::OUTPUT);
    for (int i = 0; i < 100; i++) {
        printf("ok");
        sleep_ms(10);
    }
    Leg leg = Leg();
    std::unique_ptr<Servo_DriverInterface> upperServo_driver = std::make_unique<ServoDriverLeft>(2);
    std::unique_ptr<Servo_DriverInterface> lowerServo_driver = std::make_unique<ServoDriverLeft>(3);
    // lowerServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().lowerServoAngle);
    // upperServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().upperServoAngle);
    FootTargetPosition target = FootTargetPosition(0, true);
    printf("Set:\t%d\n", leg.SetNewTargetPosition(target));
    while (1) {
        Result r = leg.LegPeriodicProcess();
        if (r == Result::RESULT_LEG_IN_TARGET_POSITION) {
            gpio.Write(1);
        }
        printf("Result:\t%d\n", r);
        printf("servoU position: %f\t", leg.p_servos.GetCurrentServoPositions().upperServoAngle);
        printf("servoL position: %f\n", leg.p_servos.GetCurrentServoPositions().lowerServoAngle);

        // gpio.Toggle();
        sleep_ms(700);
    }
}