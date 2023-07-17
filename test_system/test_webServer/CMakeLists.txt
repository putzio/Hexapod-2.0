project(test_webServer C CXX ASM)

add_executable(test_webServer test_webServer.cpp)

target_link_libraries(test_webServer 
    WEB
	DRIVERS
) 

pico_enable_stdio_usb(test_webServer 1)
pico_enable_stdio_uart(test_webServer 0)

#Generates different file formats
pico_add_extra_outputs(test_webServer)
    