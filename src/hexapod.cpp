// #include <stdio.h>
// #include <memory>
// #include "pico/stdlib.h"
// #include "hardware/pwm.h"
// #include "pico/double.h"
// #include "hardware/clocks.h"
// // #include "hardware/uart.h"
// #include "hardware/irq.h"
// #include "hardware/adc.h"
// #include "hardware/gpio.h"
// #include "hardware/i2c.h"
// #include "drivers/inc/gpio_driver.hpp"
// #include "Logic/inc/Leg.hpp"
// #include "drivers/inc/servo_driver_left.hpp"
// // #include "Leg.hpp"
// // #include "../Logic/inc/Body.hpp"
// // #include "../include/uart.hpp"
// // #include "../include/functions.h"
// // #include "../include/enum_types.h"
// // #include "../drivers/inc/pwm_driver.hpp"
// // #include "../drivers/inc/gpio_driver.hpp"
// // #include "../drivers/inc/servo_driver_left.hpp"
// // #include "../drivers/inc/servo_driver_interface.hpp"

// // const int16_t SERVO_CALIB[12] = {
// //     155,
// //     -60,
// //     -155,
// //     -80,
// //     20,
// //     95,
// //     -30,
// //     60,
// //     55,
// //     -70,
// //     90,
// //     -50};

// // bool changeVelocity = false;
// // int velocity = MIN_VELOCITY;
// // bool velocityChanged = false;
// // Mode mode = Pos90Mode;



// int main() {
//     stdio_init_all();
//     Gpio_driver gpio = Gpio_driver(25, Gpio_driver::OUTPUT);
//     for (int i = 0; i < 100; i++) {
//         printf("ok");
//         sleep_ms(10);
//     }
//     Leg leg = Leg();
//     std::unique_ptr<Servo_DriverInterface> upperServo_driver = std::make_unique<ServoDriverLeft>(2);
//     std::unique_ptr<Servo_DriverInterface> lowerServo_driver = std::make_unique<ServoDriverLeft>(3);
//     // lowerServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().lowerServoAngle);
//     // upperServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().upperServoAngle);
//     FootTargetPosition target = FootTargetPosition(0, true);
//     printf("Set:\t%d\n", leg.SetNewTargetPosition(target));
//     while (1) {
//         Result r = leg.LegPeriodicProcess();
//         if (r == Result::RESULT_LEG_IN_TARGET_POSITION) {
//             gpio.Write(1);
//         }
//         printf("Result:\t%d\n", r);
//         printf("servoU position: %f\t", leg.p_servos.GetCurrentServoPositions().upperServoAngle);
//         printf("servoL position: %f\n", leg.p_servos.GetCurrentServoPositions().lowerServoAngle);

//         // gpio.Toggle();
//         sleep_ms(700);
//     }
// }

// // void test_leg() {
#include <stdio.h>
// #include "../src/Logic/inc/Leg.hpp"
// #include "../src/drivers/inc/servo_driver_left.hpp"
// #include "../src/drivers/inc/servo_driver_right.hpp"
// #include "drivers/inc/UsbString.hpp"
// #include "hardware/spi.h"
#include "gpio.hpp"
// #include "../src/drivers/inc/servo_driver_left.hpp"
// #include <vector>

// struct SPI {
//     spi_inst_t* spi;
//     Gpio_driver* gpio_cs;
//     SPI(spi_inst_t* spi, uint32_t baudRate,
//         uint8_t rxPin, uint8_t txPin, uint8_t sckPin, uint16_t csPin,
//         uint8_t data_bits, spi_cpol_t clockPolarity, spi_cpha_t clockPhase, spi_order_t dataOrder) {
//         gpio_cs = new Gpio_driver(csPin, Gpio_driver::OUTPUT);
//         gpio_cs->Write(1);

//         spi_init(spi, baudRate);
//         spi_set_format(spi, data_bits, clockPolarity, clockPhase, dataOrder);

//         gpio_set_function(rxPin, GPIO_FUNC_SPI);
//         gpio_set_function(txPin, GPIO_FUNC_SPI);
//         gpio_set_function(sckPin, GPIO_FUNC_SPI);
//         // gpio_set_function(csPin, GPIO_FUNC_SPI);
//         this->spi = spi;
//     }
//     ~SPI() {
//         delete gpio_cs;
//     };
//     void SpiWrite(uint8_t* data, uint8_t size) {
//         spi_write_blocking(spi, data, size);
//     }
//     void SpiRead(uint8_t repeated_tx_data, uint8_t* data, uint8_t size) {
//         spi_read_blocking(spi, repeated_tx_data, data, size);
//     }
//     void SpiWriteRead(uint8_t* tx_data, uint8_t* rx_data, uint8_t size) {
//         printf("Number of bytes read: %d\n", spi_write_read_blocking(spi, tx_data, rx_data, size));
//     }
// };



// class MCP3008_SPI : public SPI {
// public:
//     MCP3008_SPI(spi_inst_t* spi, uint32_t baudRate,
//         uint8_t sckPin, uint8_t txPin, uint8_t rxPin, uint8_t csPin,
//         uint8_t data_bits, spi_cpol_t clockPolarity, spi_cpha_t clockPhase, spi_order_t dataOrder) :
//         SPI(spi, baudRate, rxPin, txPin, sckPin, csPin, data_bits, clockPolarity, clockPhase, dataOrder) {
//     }

//     uint16_t ReadChannel(uint8_t channel) {

//         // Declare data that we will send
//         uint8_t tx_data[3] = { 0 };
//         tx_data[0] = ((0x01 << 7) |		// start bit
//             (1 << 6) |			// SGL
//             ((channel & 0x07) << 3)); 	// channel number
//         tx_data[1] = 0x00;
//         tx_data[2] = 0x00;
//         // Data that we will get
//         uint8_t rx_data[3] = { 0 };

//         SpiWriteRead(tx_data, rx_data, 6);
//         gpio_cs->Write(0);
//         // SpiWrite(tx_data, 3);
//         // SpiRead(0, rx_data, 3);
//         SpiWriteRead(tx_data, rx_data, 3);
//         gpio_cs->Write(1);
//         printf("rx_data[0]: %d, %d, %d\n", rx_data[0], rx_data[1], rx_data[2]);
//         // Compute the ADC
//         return 0x3FF & ((rx_data[0] & 0x01) << 9 | (rx_data[1] & 0xFF) << 1 | (rx_data[2] & 0x80) >> 7);
//     }
// };

int main() {
    stdio_init_all();
    // printf("SPI master example\n");
    // Gpio_driver gpio = Gpio_driver(25, Gpio_driver::OUTPUT);
    // MCP3008_SPI adc_spi_0 = MCP3008_SPI(spi0, 250000, 2, 3, 4, 5, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    // uint16_t adc_0 = adc_spi_0.ReadChannel(0);
    // uint16_t adc_1 = adc_spi_0.ReadChannel(1);
    // uint16_t adc_2 = adc_spi_0.ReadChannel(2);
    // uint16_t adc_3 = adc_spi_0.ReadChannel(3);
    // uint16_t adc_4 = adc_spi_0.ReadChannel(4);
    // uint16_t adc_5 = adc_spi_0.ReadChannel(5);
    // uint16_t adc_6 = adc_spi_0.ReadChannel(6);

    // while (1) {
    //     adc_0 = adc_spi_0.ReadChannel(0);
    //     adc_1 = adc_spi_0.ReadChannel(1);
    //     adc_2 = adc_spi_0.ReadChannel(2);
    //     adc_3 = adc_spi_0.ReadChannel(3);
    //     adc_4 = adc_spi_0.ReadChannel(4);
    //     adc_5 = adc_spi_0.ReadChannel(5);
    //     adc_6 = adc_spi_0.ReadChannel(6);

    //     printf("ADC 0 value: %d\n", adc_0);
    //     printf("ADC 1 value: %d\n", adc_1);
    //     printf("ADC 2 value: %d\n", adc_2);
    //     printf("ADC 3 value: %d\n", adc_3);
    //     printf("ADC 4 value: %d\n", adc_4);
    //     printf("ADC 5 value: %d\n", adc_5);
    //     printf("ADC 6 value: %d\n", adc_6);
    //     gpio.Toggle();
    //     sleep_ms(1000);
    // }
    // std::vector<ServoDriverLeft> servos;
    // ServoDriverLeft servo = ServoDriverLeft(2);
    // servo.SetAngle(90);
    // for (int i = 0; i < 12; i++) {
    //     servos.push_back(ServoDriverLeft(i + 2));
    //     servos[i].SetAngle(90);
    // }
    using pico_drivers::Gpio;
    Gpio led = Gpio(25, Gpio::OUTPUT);
    while (1) {
        led.Toggle();
        sleep_ms(1000);
    }

}


// int main() {
//     stdio_init_all();
//     Leg leg = Leg();
//     std::unique_ptr<Servo_DriverInterface> upperServo_driver = std::make_unique<ServoDriverLeft>(2);
//     std::unique_ptr<Servo_DriverInterface> lowerServo_driver = std::make_unique<ServoDriverLeft>(3);
//     upperServo_driver->Calibrate(-50);
//     lowerServo_driver->Calibrate(60);
//     upperServo_driver->SetRadianAngle(Constants::PI / 2.0f);
//     upperServo_driver->SetRadianAngle(Constants::PI / 2.0f);
//     sleep_ms(1500);

//     upperServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().upperServoAngle);
//     lowerServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().lowerServoAngle);// sleep_ms(1000);
//     ServosPositions positions;
//     positions.upperServoAngle = Constants::PI / 2.0f;
//     positions.lowerServoAngle = Constants::PI / 3.0f;
//     leg.MoveJServos(positions);
//     while (1) {
//         if (leg.LegPeriodicProcess() == Result::RESULT_LEG_IN_TARGET_POSITION) {
//             sleep_ms(1000);
//             leg.SetNewTargetPosition(FootTargetPosition(0, true));
//         }
//         upperServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().upperServoAngle);
//         lowerServo_driver->SetRadianAngle(leg.p_servos.GetCurrentServoPositions().lowerServoAngle);

//         sleep_ms(100);
//     }
// }