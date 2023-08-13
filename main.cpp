#include "hexapod.hpp"
#include "gpio.hpp"
#include "server.hpp"
#include "cgi_handlers.hpp"
#include "pico/multicore.h"


Hexapod hexapod;
bool calibrating = true;
extern volatile int16_t calibration_values[12];

void core1_entry() {
    std::vector <tCGI> cgiHandlers;
    cgiHandlers.push_back(tCGI{ "/direction.cgi", (tCGIHandler)cgi_direction_handler });
    cgiHandlers.push_back(tCGI{ "/gait.cgi", (tCGIHandler)cgi_gait_handler });
    cgiHandlers.push_back(tCGI{ "/speed.cgi", (tCGIHandler)cgi_speed_handler });
    cgiHandlers.push_back(tCGI{ "/calibration.cgi", (tCGIHandler)cgi_calibration_handler });

    web::Server server = web::Server();
    server.Run(cgiHandlers);
    while (1)
        tight_loop_contents();
}

int main(void) {
    stdio_init_all();
    pico_drivers::Gpio cs2 = pico_drivers::Gpio(SPI_CS_FLASH_PIN, pico_drivers::Gpio::OUTPUT);
    cs2.Write(1);
    multicore_launch_core1(core1_entry);
    hexapod.SetGait(logic::gait::GaitType::TRIPOD);
    hexapod.SetDirection(logic::GaitController::Direction::FORWARD);
    hexapod.SetSpeed(1.0f);
    hexapod.GaitControllerPeriodicProcess();
    // cyw43_arch_init();
    web::Gpio_w led = web::Gpio_w();
    // pico_drivers::Gpio led = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
    led.Write(1);
    uint32_t ledPreviousCallTime = 0;
    uint32_t gaitTimer = 0;
    while (true) {
        hexapod.AdcPeriodicProcess();
        if (calibrating)
            hexapod.CalibrateServos((const std::array<int16_t, 12>&)calibration_values);
        else
            hexapod.GaitControllerPeriodicProcess();

        if (hexapod.GetTime() / 1000 - ledPreviousCallTime > 100) {
            led.Toggle();
            ledPreviousCallTime = hexapod.GetTime() / 1000;
        }
        sleep_us(20);
    }
}
