
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_single_leg_lift_and_lower C CXX)

add_executable(test_single_leg_lift_and_lower test_single_leg_lift_and_lower.cpp)

target_link_libraries(test_single_leg_lift_and_lower 
    WEB
    LOGIC
    DRIVERS
    HEXAPOD
) 

pico_enable_stdio_usb(test_single_leg_lift_and_lower 1)
pico_enable_stdio_uart(test_single_leg_lift_and_lower 0)

#Generates different file formats
pico_add_extra_outputs(test_single_leg_lift_and_lower)
    