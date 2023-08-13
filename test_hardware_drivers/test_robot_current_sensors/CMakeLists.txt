
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_robot_current_sensors C CXX)

add_executable(test_robot_current_sensors test_robot_current_sensors.cpp)

target_link_libraries(test_robot_current_sensors 
    DRIVERS
    hardware_timer
) 

pico_enable_stdio_usb(test_robot_current_sensors 1)
pico_enable_stdio_uart(test_robot_current_sensors 0)

#Generates different file formats
pico_add_extra_outputs(test_robot_current_sensors)
    