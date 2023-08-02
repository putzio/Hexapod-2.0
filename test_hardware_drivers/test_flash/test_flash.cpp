
#include <stdio.h>
#include "pico/stdlib.h"
#include "GD25VQ21B.hpp"
#include "pinout.hpp"

int main() {
    stdio_init_all();
    printf("Hello World!\n");
    sleep_ms(1000);
    pico_drivers::Gpio cs0 = pico_drivers::Gpio(SPI_CS_ADC0_PIN, pico_drivers::Gpio::OUTPUT);
    pico_drivers::Gpio cs1 = pico_drivers::Gpio(SPI_CS_ADC1_PIN, pico_drivers::Gpio::OUTPUT);
    cs0.Write(1);
    cs1.Write(1);
    pico_drivers::Flash flash = pico_drivers::Flash(
        SPI_INSTANCE,
        SPI_BAUD_RATE,
        SPI_MISO_PIN,
        SPI_MOSI_PIN,
        SPI_CLK_PIN,
        SPI_CS_FLASH_PIN,
        FLASH_WP_PIN,
        FLASH_HOLD_PIN);
    std::vector<uint8_t> oldRead = flash.Read(0x010000, 4);
    std::vector<uint8_t>written = { 0x01, 0x02, 0x03, 0x04 };
    flash.Write(0x010000, written);
    std::vector<uint8_t> newRead = flash.Read(0x010000, 4);
    std::vector<uint8_t> id = flash.ReadManufacturerId();
    while (1) {
        printf("Old: %d\t%d\t%d\t%d\r\n",
            oldRead[0], oldRead[1], oldRead[2], oldRead[3]);
        printf("New: %d\t%d\t%d\t%d\r\n",
            newRead[0], newRead[1], newRead[2], newRead[3]);
        printf("Written: %d\t%d\t%d\t%d\r\n",
            written[0], written[1], written[2], written[3]);
        printf("ID: %d\t%d\r\n", id[0], id[1]);
        sleep_ms(1000);
    }
    return 0;
}


// #include "hardware/flash.h"
// #include "pico/stdlib.h"
// #include "hardware/irq.h"
// #include "hardware/sync.h"
// #include "stdio.h"

// #define PRINTF_DEBUG

// // We're going to erase and reprogram a region 256k from the start of flash.
// // Once done, we can access this at XIP_BASE + 256k.
// #define FLASH_TARGET_OFFSET (256 * 1024)

// const uint8_t* flash_target_contents = (const uint8_t*)(XIP_BASE + FLASH_TARGET_OFFSET);

// int main(void) {
//     stdio_init_all();
//     uint16_t     temp;
//     uint8_t  resetcount_EEPROM[FLASH_PAGE_SIZE];

//     // Keep a reset count
//     temp = flash_target_contents[0] + (flash_target_contents[1] * 256);
//     temp++;

// #ifdef PRINTF_DEBUG
//     printf("Read EEPROM value = %d\r\n", temp);
// #endif

// #ifdef PRINTF_DEBUG
//     printf("YES! Erasing FLASH EEPROM - before we can reprogram it...\r\n");
// #endif
//     resetcount_EEPROM[0] = temp & 0xFF;
//     resetcount_EEPROM[1] = ((temp & 0xFF00) >> 8);
//     uint32_t ints = save_and_disable_interrupts();
//     flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
//     flash_range_program(FLASH_TARGET_OFFSET, resetcount_EEPROM, FLASH_PAGE_SIZE);
//     restore_interrupts(ints);

// #ifdef PRINTF_DEBUG
//     printf("Written back EEPROM value = %d\r\n", temp);
// #endif
// }