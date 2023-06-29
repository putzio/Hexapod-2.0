
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_tripod_foreward C CXX)

add_executable(test_tripod_foreward test_tripod_foreward.cpp)

target_link_libraries(test_tripod_foreward 
    LOGIC
    DRIVERS
    hardware_spi
) 

pico_enable_stdio_usb(test_tripod_foreward 1)
pico_enable_stdio_uart(test_tripod_foreward 0)

#Generates different file formats
pico_add_extra_outputs(test_tripod_foreward)
    