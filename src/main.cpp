#include "hexapod.hpp"
#include "gpio.hpp"
#include "server.hpp"
#include "cgi_handlers.hpp"


Hexapod hexapod;
bool calibrating = true;
extern volatile int16_t calibration_values[12];

int main(void) {
    stdio_init_all();
    std::vector <tCGI> cgiHandlers;
    cgiHandlers.push_back(tCGI{ "/direction.cgi", (tCGIHandler)cgi_direction_handler });
    cgiHandlers.push_back(tCGI{ "/gait.cgi", (tCGIHandler)cgi_gait_handler });
    cgiHandlers.push_back(tCGI{ "/speed.cgi", (tCGIHandler)cgi_speed_handler });
    cgiHandlers.push_back(tCGI{ "/calibration.cgi", (tCGIHandler)cgi_calibration_handler });

    web::Server server = web::Server();
    server.Run(cgiHandlers);
    // printf("\n\nHello World\n");
    hexapod.SetGait(logic::gait::GaitType::MONOCHROMATIC);
    hexapod.SetDirection(logic::GaitController::Direction::FORWARD);
    hexapod.PeriodicProcess();
    web::Gpio_w led = web::Gpio_w();
    led.Write(1);
    while (true) {
        if (calibrating) {
            hexapod.CalibrateServos((const std::array<int16_t, 12>&)calibration_values);
        }
        else {
            hexapod.PeriodicProcess();
        }
        led.Toggle();
        sleep_ms(50);
    }
}
