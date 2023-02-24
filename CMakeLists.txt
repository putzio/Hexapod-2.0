#specify a min ver
cmake_minimum_required(VERSION 3.19)

#INCLUDE THE CMAKE IMPORT FILE
# include(pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
add_library(LOGIC)
add_library(DRIVERS)
add_library(WALKING_MODES)

add_subdirectory(drivers)
add_subdirectory(Logic)
add_subdirectory(WalkingModes)

project(Hexapod C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#inintialise the sdk
pico_sdk_init()

#Creating an executable target "Hexapod" from a single source hexapod.cpp
add_executable(${PROJECT_NAME} 
    ./src/hexapod.cpp
)
#libraries
target_link_libraries(${PROJECT_NAME} 
    LOGIC
    DRIVERS
    WALKING_MODES
) 

#Generates different file formats
pico_add_extra_outputs(Hexapod)