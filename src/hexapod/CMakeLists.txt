target_link_libraries(HEXAPOD  
    WEB
	DRIVERS
    LOGIC
) 

target_sources(HEXAPOD PRIVATE
    ./src/robot_driver.cpp
    ./src/hexapod.cpp
)

target_include_directories(HEXAPOD PUBLIC inc)