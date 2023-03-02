#include "../inc/test_pwm.hpp"

std::shared_ptr<Pwm_driver> test_pwm_setup(uint8_t pin) {
    // stdio_init_all;
    std::shared_ptr<Pwm_driver> driver = std::make_shared<Pwm_driver>(25);
    driver->Enable();
    return driver;
}
void test_pwm_loop(std::shared_ptr<Pwm_driver> driver, uint16_t* counter) {
    driver->SetPwm(*counter);
    *counter += 10;
    if (*counter > 15000) {
        *counter = 100;
    }
    sleep_ms(1);
}
