message("Running makefsdata python script")

execute_process(COMMAND
    python3 makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")

target_include_directories(WEB PUBLIC ./inc)

target_sources(WEB PUBLIC
    ./src/cgi.cpp
    ./src/ssi.cpp
    ./src/gpio_w.cpp
    ./src/server.cpp
)

target_link_libraries(WEB PUBLIC
    pico_cyw43_arch_lwip_threadsafe_background
    pico_stdlib
    pico_lwip_http
    hardware_adc
)