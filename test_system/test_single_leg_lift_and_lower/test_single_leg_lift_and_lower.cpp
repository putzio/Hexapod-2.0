#include "hexapod.hpp"
#include "gpio.hpp"
#include "server.hpp"
#include "cgi_handlers.hpp"


Hexapod hexapod;
bool calibrating = true;
extern volatile int16_t calibration_values[12];

int main(void) {
    stdio_init_all();
    pico_drivers::Gpio cs2 = pico_drivers::Gpio(SPI_CS_FLASH_PIN, pico_drivers::Gpio::OUTPUT);
    cs2.Write(1);
    hexapod.SetGait(logic::gait::GaitType::TRIPOD);
    hexapod.SetDirection(logic::GaitController::Direction::FORWARD);
    hexapod.SetSpeed(1.0f);
    hexapod.GaitControllerPeriodicProcess();
    cyw43_arch_init();
    web::Gpio_w led = web::Gpio_w();
    // pico_drivers::Gpio led = pico_drivers::Gpio(25, pico_drivers::Gpio::OUTPUT);
    led.Write(1);
    uint32_t ledPreviousCallTime = 0;
    uint32_t gaitTimer = 0;

    //mine:
    std::array<uint8_t, 12> pins;
    for (int i; i < pins.size(); i++) {
        pins[i] = i + FIRST_SERVO_PIN;
    }
    pico_drivers::LegsController legsController = pico_drivers::LegsController(pins);
    legsController.InitServos();

    std::array<logic::leg::LegServos, 6> legs;
    std::array<logic::leg::ServosPositions, 6> newAngles;
    for (int i = 0; i < legs.size(); i++) {
        legs[i] = logic::leg::LegServos(Constants::PI / 2.0, Constants::PI / 2.0);
        legs[i].SetTargetAngle(Constants::PI * 60.0f / 180.0f, 0.01f, Constants::PI * 150.0f / 180.0f, 0.01f);
        if (i > 3) {
            legs[i].SetTargetAngle(Constants::PI * 120.0f / 180.0f, 0.01f, Constants::PI * 30.0f / 180.0f, 0.01f);
        }
        newAngles[i] = legs[i].GetCurrentServoPositions();
    }
    legsController.UpdateServos(newAngles);
    led.Toggle();
    sleep_ms(1000);

    hexapod.CalibrateServos((const std::array<int16_t, 12>&)calibration_values);

    uint32_t t = hexapod.GetTime()/1000;
    uint32_t legT = hexapod.GetTime()/1000;

    while (true) {
        hexapod.AdcPeriodicProcess();
        if (hexapod.GetTime() / 1000 - ledPreviousCallTime > 100) {
            led.Toggle();
            ledPreviousCallTime = hexapod.GetTime() / 1000;
        }

        if (hexapod.GetTime()/1000 - t > 25) {
            t = hexapod.GetTime()/1000;
            for (int i = 0; i < legs.size(); i++) {
                legs[i].GoToTargetAngles();
                newAngles[i] = legs[i].GetCurrentServoPositions();
            }
            legsController.UpdateServos(newAngles);
        }
        if (hexapod.GetTime()/1000 - legT > 2000) {
            legs[0].SetTargetAngle(Constants::PI * 45.0f / 180.0f, 0.01f, Constants::PI / 2.0, 0.01f);
        }
        if (hexapod.GetTime()/1000 - legT > 5000) {
            legs[0].SetTargetAngle(Constants::PI * 70.0f / 180.0f, 0.01f, Constants::PI / 2.0, 0.01f);
            legT = hexapod.GetTime()/1000;
        }

        sleep_us(20);
    }
}
