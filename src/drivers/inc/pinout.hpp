#pragma once

#define FIRST_SERVO_PIN 6
#define LAST_SERVO_PIN 17

#define SPI_CLK_PIN 2
#define SPI_MOSI_PIN 3
#define SPI_MISO_PIN 4

#define SPI_CS_ADC0_PIN 5
#define SPI_CS_ADC1_PIN 22
#define SPI_CS_FLASH_PIN 28

#define I2C_SDA_PIN 20
#define I2C_SCL_PIN 21

#define FLASH_HOLD_PIN 27
#define FLASH_WP_PIN 26

#define SPI_INSTANCE spi0
#define SPI_BAUD_RATE 250000

#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UART_ID uart0
#define UART_BAUD_RATE 115200