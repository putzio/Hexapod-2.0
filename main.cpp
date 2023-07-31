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
    // std::vector <tCGI> cgiHandlers;
    // cgiHandlers.push_back(tCGI{ "/direction.cgi", (tCGIHandler)cgi_direction_handler });
    // cgiHandlers.push_back(tCGI{ "/gait.cgi", (tCGIHandler)cgi_gait_handler });
    // cgiHandlers.push_back(tCGI{ "/speed.cgi", (tCGIHandler)cgi_speed_handler });
    // cgiHandlers.push_back(tCGI{ "/calibration.cgi", (tCGIHandler)cgi_calibration_handler });

    // web::Server server = web::Server();
    // server.Run(cgiHandlers);
    // printf("\n\nHello World\n");
    multicore_launch_core1(core1_entry);
    hexapod.SetGait(logic::gait::GaitType::MONOCHROMATIC);
    hexapod.SetDirection(logic::GaitController::Direction::FORWARD);
    hexapod.PeriodicProcess();
    web::Gpio_w led = web::Gpio_w();
    led.Write(1);
    while (true) {
        if (calibrating) {
            hexapod.CalibrateServos((const std::array<int16_t, 12>&)calibration_values);
            led.Write(0);
        }
        else {
            hexapod.PeriodicProcess();
            led.Write(1);
        }
        sleep_us(20);
    }
}
