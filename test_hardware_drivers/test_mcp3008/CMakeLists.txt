
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

project(test_mcp3008 C CXX)

add_executable(test_mcp3008 test_mcp3008.cpp)

target_link_libraries(test_mcp3008 
    LOGIC
    DRIVERS
) 

pico_enable_stdio_usb(test_mcp3008 1)
pico_enable_stdio_uart(test_mcp3008 0)

#Generates different file formats
pico_add_extra_outputs(test_mcp3008)