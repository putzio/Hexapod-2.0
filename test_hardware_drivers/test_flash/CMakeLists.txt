
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_flash C CXX)

add_executable(test_flash test_flash.cpp)

target_link_libraries(test_flash 
    DRIVERS
) 

pico_enable_stdio_usb(test_flash 1)
pico_enable_stdio_uart(test_flash 0)

#Generates different file formats
pico_add_extra_outputs(test_flash)
    