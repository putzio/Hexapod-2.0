
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_leg C CXX)

add_executable(test_leg test_leg.cpp)

target_link_libraries(test_leg 
    LOGIC
    DRIVERS
    hardware_spi
) 

pico_enable_stdio_usb(test_leg 1)
pico_enable_stdio_uart(test_leg 0)

#Generates different file formats
pico_add_extra_outputs(test_leg)
    