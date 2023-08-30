cmake_minimum_required(VERSION 3.19)

set(PICO_BOARD pico_w)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# # Download and unpack googletest at configure time
# configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
# execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#   RESULT_VARIABLE result
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
# if(result)
#   message(FATAL_ERROR "CMake step for googletest failed: ${result}")
# endif()
# execute_process(COMMAND ${CMAKE_COMMAND} --build .
#   RESULT_VARIABLE result
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
# if(result)
#   message(FATAL_ERROR "Build step for googletest failed: ${result}")
# endif()

# # Prevent overriding the parent project's compiler/linker
# # settings on Windows
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# # Add googletest directly to our build. This defines
# # the gtest and gtest_main targets.
# add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
#                  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
#                  EXCLUDE_FROM_ALL)

# # The gtest/gtest_main targets carry header search path
# # dependencies automatically when using CMake 2.8.11 or
# # later. Otherwise we have to add them here ourselves.
# if (CMAKE_VERSION VERSION_LESS 2.8.11)
#   include_directories("${gtest_SOURCE_DIR}/include")
# endif()

# enable_testing()
# set(FLAGS -Wall -Werror -Wconversion -g)

# add_compile_options(${FLAGS})

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(app CXX C ASM)

pico_sdk_init()

add_library(WEB)
add_subdirectory(src/web)
add_library(DRIVERS)
add_subdirectory(src/drivers)
add_library(LOGIC)
add_subdirectory(src/Logic)

add_library(HEXAPOD)
add_subdirectory(src/hexapod)

add_subdirectory(test_system)
add_subdirectory(test_hardware_drivers)

target_include_directories(
    LOGIC PUBLIC ./include
    DRIVERS PUBLIC ./include
    # ${PROJECT_NAME} ./include
    # WEB PUBLIC ./src/drivers/inc
    # ${PROJECT_NAME} PUBLIC ./include
)

add_executable(${PROJECT_NAME} 
    ./main.cpp
)

target_link_libraries(${PROJECT_NAME}  
    WEB
    LOGIC
    DRIVERS
    HEXAPOD
    pico_multicore
) 

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} TRUE)
pico_enable_stdio_uart(${PROJECT_NAME} TRUE)

#Generates different file formats
pico_add_extra_outputs(${PROJECT_NAME})