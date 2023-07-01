
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_gpio C CXX)

add_executable(test_gpio test_gpio.cpp)

target_link_libraries(test_gpio 
    LOGIC
    DRIVERS
) 

pico_enable_stdio_usb(test_gpio 1)
pico_enable_stdio_uart(test_gpio 0)

#Generates different file formats
pico_add_extra_outputs(test_gpio)