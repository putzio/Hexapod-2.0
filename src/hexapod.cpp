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
#include "Body.hpp"
#include "uart.hpp"
#include "functions.h"
#include "enum_types.h"


const int16_t SERVO_CALIB[12] = {
    155,
    -60,
    -155,
    -80,
    20,
    95,
    -30,
    60,
    55,
    -70,
    90,
    -50};

bool changeVelocity = false;
int velocity = MIN_VELOCITY;
bool velocityChanged = false;
Mode mode = Pos90Mode;

int main()
{
    stdio_init_all();

    gpio_init(BUILD_IN_LED);
    gpio_set_dir(BUILD_IN_LED, GPIO_OUT);

    InitUart();
    ADC_INIT();
    MeasureBattery();

    uint8_t mser[6], sser[6];
    for (int i = 0; i < ARRAY_SIZE(mser); i++)
    {
        mser[i] = 2 * (i + 1); //(i+1) because we start at gpio 2
        sser[i] = 2 * (i + 1) + 1;
    }

    Body body(mser, sser, SERVO_CALIB);

    if (MeasureBattery())
        body.ModeChanged(mode);

    while (1)
    {
        if (!MeasureBattery())
        {
            body.DisableLegs();
            sleep_ms(10000);
        }
        else
        {
            if (velocityChanged)
            {
                body.ChangeBodyVelocityLimits(velocity);
            }
            // enableProgram = MeasureBattery();
            if (mode != body.modeType)
            {
                body.ModeChanged(mode);
            }
            gpio_put(BUILD_IN_LED, 1);
            do
            {
                body.Move();
                sleep_ms(20); // 20
            } while (!body.MovesDone());

            gpio_put(BUILD_IN_LED, 0);
        }
        sleep_ms(20);
    }
}