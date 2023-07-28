#include "hexapod.hpp"
#include "gpio.hpp"

int main(void) {
    stdio_init_all();
    // printf("\n\nHello World\n");
    Hexapod hexapod = Hexapod();
    hexapod.SetGait(logic::gait::GaitType::CATERPILLAR);
    hexapod.SetDirection(logic::GaitController::Direction::FOREWARD);
    pico_drivers::Gpio led = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
    while (true) {
        hexapod.PeriodicProcess();
        led.Toggle();
        sleep_ms(100);
    }
}
