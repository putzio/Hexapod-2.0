
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_ground_detection C CXX)

add_executable(test_ground_detection test_ground_detection.cpp)

target_link_libraries(test_ground_detection 
    WEB
    LOGIC
    DRIVERS
    HEXAPOD
) 

pico_enable_stdio_usb(test_ground_detection 1)
pico_enable_stdio_uart(test_ground_detection 0)

#Generates different file formats
pico_add_extra_outputs(test_ground_detection)
    