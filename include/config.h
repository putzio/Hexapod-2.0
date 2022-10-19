#pragma once
//----------------------my program-------------------------------------------------
#define UART_ID uart0
#define BAUD_RATE 9600

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

// pins
#define RX_PIN 1
#define TX_PIN 0
// Servos - 2-13
#define LED_VIN_LOW 26
#define EN_VIN_CHECK 27
#define VIN_CHECK_GPIO 28
#define VIN_CHECK_A_INPUT (VIN_CHECK_GPIO - 26)
#define BUILD_IN_LED 25

#define LED_PIN 15

// Measure Battery
#define RESISTOR_3 4700          // OHM
#define RESISTOR_2 10000         // OHM
#define RP_VOLTAGE 3.3           // V
#define MIN_BATTERY_VOLATAGE 7.0 // V
#define ADC_MAX 4096             // 12-bit
#define RESISTOR_3_MIN_VOLTAGE (MIN_BATTERY_VOLATAGE / (RESISTOR_2 + RESISTOR_3) * RESISTOR_3)
#define MIN_ADC_VALUE (RESISTOR_3_MIN_VOLTAGE * ADC_MAX / RP_VOLTAGE)
