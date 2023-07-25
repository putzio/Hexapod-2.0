
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_caterpillar_foreward C CXX)

add_executable(test_caterpillar_foreward test_caterpillar_foreward.cpp)

target_link_libraries(test_caterpillar_foreward 
    LOGIC
	DRIVERS
) 

pico_enable_stdio_usb(test_caterpillar_foreward 1)
pico_enable_stdio_uart(test_caterpillar_foreward 0)

#Generates different file formats
pico_add_extra_outputs(test_caterpillar_foreward)
    