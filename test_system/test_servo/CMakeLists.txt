
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_servo C CXX)

add_executable(test_servo test_servo.cpp)

target_link_libraries(test_servo 
    LOGIC
    DRIVERS
    hardware_spi
) 

pico_enable_stdio_usb(test_servo 1)
pico_enable_stdio_uart(test_servo 0)

#Generates different file formats
pico_add_extra_outputs(test_servo)
    