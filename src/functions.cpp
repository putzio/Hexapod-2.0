#include "functions.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "config.h"
#include "hardware/adc.h"

void Message(bool& changeVelocity, bool& velocityChanged, int& velocity, enum Mode& mode, char& recMode)
{
    if (changeVelocity)
    {
        if (recMode == '&')
        {
            velocityChanged = true;
            changeVelocity = false;
        }
        else
        {
            velocity *= 10;
            velocity += (int)recMode - 48;
        }
    }
    else
    {
        switch (recMode)
        {
        case 'f':
            mode = ForwardMode;
            break;
        case 'b':
            mode = BackMode;
            break;
        case 'l':
            mode = LeftMode;
            break;
        case 'r':
            mode = RightMode;
            break;
        case 's':
            mode = StopMode;
            break;
        case 'R':
            mode = ResetMode;
            break;
        case 'P':
            mode = Pos90Mode;
            break;
        case 'V':
        {
            changeVelocity = true;
            velocity = 0;
            break;
        }
        }
    }
}

void ADC_INIT()
{
    // init ADC
    adc_init();
    // // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(VIN_CHECK_GPIO);
    // Select ADC input 0 (GPIO26)
    adc_select_input(VIN_CHECK_A_INPUT);
    // set LED and gpio, which turns on the transistor as output
    gpio_init(LED_VIN_LOW);
    gpio_set_dir(LED_VIN_LOW, GPIO_OUT);
    // gpio_put(LED_VIN_LOW,1);
    gpio_init(EN_VIN_CHECK);
    gpio_set_dir(EN_VIN_CHECK, GPIO_OUT);
    gpio_init(BUILD_IN_LED);
    gpio_set_dir(BUILD_IN_LED, GPIO_OUT);
}
bool MeasureBattery()
{
    // turn on the transistor
    gpio_put(EN_VIN_CHECK, 1);
    sleep_ms(100);
    // measure voltage
    uint16_t result = adc_read();
    gpio_put(EN_VIN_CHECK, 0);
    if (result < MIN_ADC_VALUE)
    {
        for (int i = 0; i < 3; i++)
        {
            gpio_put(LED_VIN_LOW, 1);
            gpio_put(BUILD_IN_LED, 1);
            sleep_ms(500);
            gpio_put(LED_VIN_LOW, 0);
            gpio_put(BUILD_IN_LED, 0);
            sleep_ms(500);
        }
        return false;
    }
    return true;
}