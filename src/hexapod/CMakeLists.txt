target_link_libraries(HEXAPOD  
    WEB
	DRIVERS
    LOGIC
    hardware_timer
) 

target_sources(HEXAPOD PRIVATE
    ./src/hexapod.cpp
    ./src/cgi_handlers.cpp
)

target_include_directories(HEXAPOD PUBLIC inc)