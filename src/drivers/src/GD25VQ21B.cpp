#include "GD25VQ21B.hpp"

#define FLASH_PAGE_SIZE        256
#define FLASH_SECTOR_SIZE      4096

#define FLASH_CMD_PAGE_PROGRAM 0x02
#define FLASH_CMD_READ         0x03
#define FLASH_CMD_STATUS       0x05
#define FLASH_CMD_WRITE_EN     0x06
#define FLASH_CMD_SECTOR_ERASE 0x20

#define FLASH_STATUS_BUSY_MASK 0x01

namespace pico_drivers {
    Flash::Flash(spi_inst_t* spi, uint32_t baudRate,
        uint8_t rxPin, uint8_t txPin, uint8_t sckPin, uint16_t csPin, uint8_t writeProtectPin, uint8_t holdInputPin)
        :SPI(spi, baudRate, rxPin, txPin, sckPin, csPin, data_bits, clockPolarity, clockPhase, dataOrder),
        gpio_writeProtect(writeProtectPin, Gpio::OUTPUT),
        gpio_holdInput(holdInputPin, Gpio::OUTPUT) {
        gpio_writeProtect.Write(0);
    }
    std::vector<uint8_t> Flash::Read(uint32_t address, uint32_t length) {
        std::vector<uint8_t> data = std::vector<uint8_t>(1 + 3 + length);
        std::vector<uint8_t> txData = std::vector<uint8_t>(1 + 3 + length);
        txData[0] = GD25VQ21B_READ_DATA;
        txData[1] = (uint8_t)(address >> 16);
        txData[2] = (uint8_t)(address >> 8);
        txData[3] = (uint8_t)(address >> 0);
        gpio_cs->Write(0);
        SpiWriteRead(txData.data(), data.data(), 1 + 3 + length);
        gpio_cs->Write(1);
        return data;
    }
    void Flash::Write(uint32_t address, std::vector<uint8_t> data) {
        WriteEnable();
        std::vector<uint8_t> txData = std::vector<uint8_t>(1 + 3 + data.size());
        txData[0] = GD25VQ21B_WRITE_PAGE;
        txData[1] = (uint8_t)(address >> 16);
        txData[2] = (uint8_t)(address >> 8);
        txData[3] = (uint8_t)(address >> 0);
        for (int i = 0; i < data.size(); i++) {
            txData[4 + i] = data[i];
        }
        gpio_cs->Write(0);
        sleep_ms(1);
        SpiWrite(txData.data(), 1 + 3 + data.size());
        gpio_cs->Write(1);
        WriteDisable();
    }

    std::vector<uint8_t> Flash::ReadManufacturerId() {
        std::vector<uint8_t> data = std::vector<uint8_t>(2);
        uint8_t command[] = { GD25VQ21B_READ_MANUFACTURER_ID };
        gpio_cs->Write(0);
        sleep_ms(1);
        SpiWrite(command, 1);
        SpiRead(0, data.data(), 2);
        gpio_cs->Write(1);
        return data;
    }

    void Flash::Erase(uint32_t address, uint32_t length) {

    }

    void Flash::WriteEnable() {
        uint8_t command = GD25VQ21B_WRITE_ENABLE;
        gpio_writeProtect.Write(1);
        gpio_cs->Write(0);
        sleep_ms(1);
        SpiWrite(&command, 1);
        gpio_cs->Write(1);
    }
    void Flash::WriteDisable() {
        uint8_t command = GD25VQ21B_WRITE_DISABLE;
        gpio_cs->Write(0);
        sleep_ms(1);
        SpiWrite(&command, 1);
        gpio_cs->Write(1);
        gpio_writeProtect.Write(0);
    }
    void Flash::WaitUntilReady() {

    }
    void Flash::EraseSector(uint32_t address) {

    }
    void Flash::EraseBlock(uint32_t address) {

    }
    void Flash::EraseChip() {

    }
}