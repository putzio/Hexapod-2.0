#pragma once

#include "spi.hpp"
#include "gpio.hpp"
#include <vector>

// #define WRITE_ENABLE 0x06
// #define WRITE_DISABLE 0x04
// #define READ_STATUS_REGISTER_1 0x05
// #define READ_STATUS_REGISTER_2 0x35
// #define WRITE_STATUS_REGISTER 0x01
// #define WRITE_STATUS_REGISTER_2 0x31
// #define PAGE_PROGRAM 0x02
// #define QUAD_PAGE_PROGRAM 0x32
// #define SECTOR_ERASE 0x20
// #define BLOCK_ERASE_32K 0x52
// #define BLOCK_ERASE_64K 0xD8
// #define CHIP_ERASE 0xC7
// #define ERASE_SUSPEND 0x75
// #define ERASE_RESUME 0x7A
// #define POWER_DOWN 0xB9
// #define HIGH_PERFORMANCE 0xA3
// #define MODE_BIT_RESET 0xFF

// #define READ_DATA 0x03
// #define FAST_READ 0x0B
// #define FAST_READ_DUAL_OUTPUT 0x3B
// #define FAST_READ_QUAD_OUTPUT 0x6B
// #define FAST_READ_DUAL_IO 0xBB
// #define FAST_READ_QUAD_IO 0xEB
// #define WORD_READ_QUAD_IO 0xE7
// #define OCTAL_WORD_READ_QUAD_IO 0xE3
// #define JEDEC_ID 0x9F
// #define READ_UNIQUE_ID 0x4B
// #define READ_SFDP_REGISTER 0x5A
// #define READ_BLOCK_PROTECTION_REGISTER 0x72
// #define GLOBAL_BLOCK_PROTECTION_UNLOCK 0x98
// #define READ_SECURITY_REGISTER 0x48
// #define PROGRAM_SECURITY_REGISTER 0x42
// #define READ_LOCK_REGISTER 0x7E
// #define WRITE_LOCK_REGISTER 0x7D
// #define READ_NONVOLATILE_CONFIGURATION_REGISTER 0xB5
// #define WRITE_NONVOLATILE_CONFIGURATION_REGISTER 0xB1
// #define READ_VOLATILE_CONFIGURATION_REGISTER 0x85
// #define WRITE_VOLATILE_CONFIGURATION_REGISTER 0x81
// #define READ_ENHANCED_VOLATILE_CONFIGURATION_REGISTER 0x65
// #define WRITE_ENHANCED_VOLATILE_CONFIGURATION_REGISTER 0x61

#define GD25VQ21B_READ_DATA            0x03
#define GD25VQ21B_WRITE_ENABLE         0x06
#define GD25VQ21B_WRITE_DISABLE        0x04
#define GD25VQ21B_READ_STATUS_REG      0x05
#define GD25VQ21B_WRITE_STATUS_REG     0x01
#define GD25VQ21B_SECTOR_ERASE         0x20
#define GD25VQ21B_BLOCK_ERASE          0xD8
#define GD25VQ21B_CHIP_ERASE           0xC7
#define GD25VQ21B_READ_ID              0x9F
#define GD25VQ21B_READ_UNIQUE_ID       0x4B
#define GD25VQ21B_WRITE_PAGE           0x02
#define GD25VQ21B_READ_MANUFACTURER_ID 0x92


namespace pico_drivers {
    class Flash :SPI {
    public:
        Flash(spi_inst_t* spi, uint32_t baudRate,
            uint8_t rxPin, uint8_t txPin, uint8_t sckPin, uint16_t csPin, uint8_t writeProtectPin, uint8_t holdInputPin);
        std::vector<uint8_t> Read(uint32_t address, uint32_t length);
        void Write(uint32_t address, std::vector<uint8_t> data);
        void Erase(uint32_t address, uint32_t length);
        std::vector<uint8_t> ReadManufacturerId();
    private:
        void WriteEnable();
        void WriteDisable();
        void WaitUntilReady();
        void EraseSector(uint32_t address);
        void EraseBlock(uint32_t address);
        void EraseChip();

        Gpio gpio_writeProtect;
        Gpio gpio_holdInput;
        const uint8_t data_bits = 8;
        const spi_cpol_t clockPolarity = SPI_CPOL_0;
        const spi_cpha_t clockPhase = SPI_CPHA_0;
        const spi_order_t dataOrder = SPI_MSB_FIRST;
    };
}