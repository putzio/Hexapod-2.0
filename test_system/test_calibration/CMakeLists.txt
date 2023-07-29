
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_calibration C CXX)

add_executable(test_calibration test_calibration.cpp)

target_link_libraries(test_calibration 
    WEB    
    LOGIC
	DRIVERS
) 

pico_enable_stdio_usb(test_calibration 1)
pico_enable_stdio_uart(test_calibration 0)

#Generates different file formats
pico_add_extra_outputs(test_calibration)
    