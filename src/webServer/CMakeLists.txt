message("Running makefsdata python script")

execute_process(COMMAND
    py makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
# target_include_directories(WEB PRIVATE
#     ${CMAKE_CURRENT_LIST_DIR}
# )

target_include_directories(WEB PUBLIC inc
    WEB PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)


target_sources(LOGIC PUBLIC
    ./src/cgi.cpp
    ./src/ssi.cpp
)

target_link_libraries(WEB
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
)

