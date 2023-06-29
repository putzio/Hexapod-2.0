# target_include_directories(TEST_HW PUBLIC inc)

# include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# pico_sdk_init()

# target_sources(TEST_HW
#     PUBLIC src/test_gpio.cpp
#     PUBLIC src/test_pwm.cpp
#     PUBLIC src/test_servo.cpp
#     )

# target_link_libraries(TEST_HW PUBLIC
#     DRIVERS
#     pico_stdlib
#     hardware_pwm
#     hardware_clocks
#     hardware_uart
#     pico_double
#     hardware_irq
#     hardware_adc
#     hardware_gpio
# ) 