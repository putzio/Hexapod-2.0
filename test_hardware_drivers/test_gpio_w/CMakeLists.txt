
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_gpio_w C CXX)

add_executable(test_gpio_w test_gpio_w.cpp)

target_link_libraries(test_gpio_w 
    WEB
) 

pico_enable_stdio_usb(test_gpio_w 1)
pico_enable_stdio_uart(test_gpio_w 0)

#Generates different file formats
pico_add_extra_outputs(test_gpio_w)
    