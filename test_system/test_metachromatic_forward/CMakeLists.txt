
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_metachromatic_forward C CXX)

add_executable(test_metachromatic_forward test_metachromatic_forward.cpp)

target_link_libraries(test_metachromatic_forward 
    LOGIC
	DRIVERS
) 

pico_enable_stdio_usb(test_metachromatic_forward 1)
pico_enable_stdio_uart(test_metachromatic_forward 0)

#Generates different file formats
pico_add_extra_outputs(test_metachromatic_forward)
    