cmake_minimum_required(VERSION 3.19)

set(PICO_BOARD pico_w)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(hexapod CXX C ASM)

pico_sdk_init()

add_library(WEB)
add_subdirectory(src/web)
add_library(DRIVERS)
add_subdirectory(src/drivers)
add_library(LOGIC)
add_subdirectory(src/Logic)

add_subdirectory(test_system)
add_subdirectory(test_hardware_drivers)

target_include_directories(
    LOGIC PUBLIC ./include
    DRIVERS PUBLIC ./include
    # ${PROJECT_NAME} PUBLIC ./include
)

add_executable(${PROJECT_NAME} src/hexapod.cpp)

#libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    WEB
    LOGIC
    DRIVERS
) 

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} TRUE)
pico_enable_stdio_uart(${PROJECT_NAME} FALSE)

#Generates different file formats
pico_add_extra_outputs(${PROJECT_NAME})