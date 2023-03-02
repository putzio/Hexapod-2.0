#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/double.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
// #include "Servo.h"
// #include "Leg.hpp"
#include "../Logic/inc/Body.hpp"
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
    uint16_t topCounterValue = 20000;
    uint8_t integerPrescaler_8b = 125;
    uint8_t fractionalPrescaler_4b = 9;
    stdio_init_all();
    // Pwm_driver driver = Pwm_driver(25);
    // // Servo_DriverInterface* servo;
    // // *servo = ServoDriverLeft(25);
    // // ServoDriverLeft servo = ServoDriverLeft(0);
    // // servo->SetAngle(90);
    // // servo->TestPWM();
    // driver.SetPwm(10000);
    // driver.Enable();
    uint16_t slice_num;
    gpio_set_function(25, GPIO_FUNC_PWM);
    // Find out which PWM slice is connected to GPIO
    slice_num = pwm_gpio_to_slice_num(25);
    // Set period of 20000 cycles (0 to 20000 inclusive)
    pwm_set_wrap(slice_num, topCounterValue);
    // setting period = 20ms
    // set clk div to 38
    pwm_set_clkdiv_int_frac(slice_num, integerPrescaler_8b, fractionalPrescaler_4b);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(25), 10000);
    pwm_set_enabled(slice_num, true);

    while (1) {
        sleep_ms(5);
    }
}