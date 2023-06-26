#specify a min ver
cmake_minimum_required(VERSION 3.19)

#INCLUDE THE CMAKE IMPORT FILE
# include(pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
add_library(LOGIC)
add_library(DRIVERS)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

project(Hexapod C CXX)

add_subdirectory(src/drivers)
add_subdirectory(src/Logic)
add_subdirectory(test_combined)

# unit tests:
# add_subdirectory(test)
# add_subdirectory(extern)




#inintialise the sdk
pico_sdk_init()

target_include_directories(
    LOGIC PUBLIC ./include
    LOGIC PUBLIC ./src/Logic/inc
    DRIVERS PUBLIC ./include
    DRIVERS PUBLIC ./src/drivers/inc
    Hexapod PUBLIC ./include
)

#Creating an executable target "Hexapod" from a single source hexapod.cpp
add_executable(${PROJECT_NAME} 
    ./src/hexapod.cpp
)
# enable usb output, disable uart output
pico_enable_stdio_usb(Hexapod 1)
pico_enable_stdio_uart(Hexapod 0)
#libraries
target_link_libraries(${PROJECT_NAME} 
    LOGIC
    DRIVERS
    hardware_spi
) 
#Generates different file formats
pico_add_extra_outputs(Hexapod)


if(TEST_HARDWARE)
    project(TEST_HARDWARE C CXX)
    
    add_executable(TEST_HARDWARE 
    ./test/test.cpp
    )
    # enable usb output, disable uart output
    pico_enable_stdio_usb(TEST_HARDWARE 1)
    pico_enable_stdio_uart(TEST_HARDWARE 0)
    add_library(TEST_HW)
    add_subdirectory(./test/test_hw)
    #libraries
    target_link_libraries(TEST_HARDWARE 
        DRIVERS
        TEST_HW
        hardware_i2c
    ) 
    
    #Generates different file formats
    pico_add_extra_outputs(TEST_HARDWARE)
# else()
#     #add some other compilation flags
endif(TEST_HARDWARE)
unset(TEST_HARDWARE CACHE) # <---- this is the important!!

