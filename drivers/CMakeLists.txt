
target_include_directories(DRIVERS PUBLIC inc)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

target_sources(DRIVERS PUBLIC
    ./src/pwm_driver.cpp
    ./src/body_driver.cpp
    )

target_link_libraries(DRIVERS PUBLIC
    pico_stdlib
    hardware_pwm
    hardware_clocks
    hardware_uart
    pico_double
    hardware_irq
    hardware_adc
    hardware_gpio
) 
