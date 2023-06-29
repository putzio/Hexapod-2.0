
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_pwm C CXX)

add_executable(test_pwm test_pwm.cpp)

target_link_libraries(test_pwm 
    LOGIC
    DRIVERS
) 

pico_enable_stdio_usb(test_pwm 1)
pico_enable_stdio_uart(test_pwm 0)

#Generates different file formats
pico_add_extra_outputs(test_pwm)
    
add_subdirectory(test_pwm)