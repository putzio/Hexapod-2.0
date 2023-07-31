
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_uart C CXX)

add_executable(test_uart test_uart.cpp)

target_link_libraries(test_uart 
    DRIVERS
) 

pico_enable_stdio_usb(test_uart 0)
pico_enable_stdio_uart(test_uart 1)

#Generates different file formats
pico_add_extra_outputs(test_uart)
    