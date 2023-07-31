
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_monochromatic_forward C CXX)

add_executable(test_monochromatic_forward test_monochromatic_forward.cpp)

target_link_libraries(test_monochromatic_forward 
    LOGIC
	DRIVERS
) 

pico_enable_stdio_usb(test_monochromatic_forward 1)
pico_enable_stdio_uart(test_monochromatic_forward 0)

#Generates different file formats
pico_add_extra_outputs(test_monochromatic_forward)
    