
target_include_directories(DRIVERS PUBLIC inc
DRIVERS PUBLIC ../../include)

target_sources(DRIVERS
    PUBLIC ./src/pwm.cpp
    PUBLIC ./src/gpio.cpp
    PUBLIC ./src/servo_interface.cpp
    PUBLIC ./src/servo_right.cpp
    PUBLIC ./src/servo_left.cpp
    PUBLIC ./src/mcp3008.cpp
    PUBLIC ./src/spi.cpp
    PUBLIC ./src/legs_controller.cpp
    PUBLIC ./src/robot_current_sensors.cpp
    PUBLIC ./src/GD25VQ21B.cpp
    PUBLIC ./src/uart.cpp
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
    hardware_i2c
    hardware_spi
    hardware_uart
    LOGIC
) 
