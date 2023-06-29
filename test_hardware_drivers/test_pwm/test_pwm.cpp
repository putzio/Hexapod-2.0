#include "pwm.hpp"
#include <memory>

int main() {
    using namespace pico_drivers;
    stdio_init_all();
    std::shared_ptr<Pwm> driver = std::make_shared<Pwm>(25);
    driver->Enable();
    uint16_t counter = 100;
    while (1) {
        driver->SetPwm(counter);
        counter += 10;
        if (counter > 15000) {
            counter = 100;
        }
        sleep_ms(1);
    }
    return 0;
}
