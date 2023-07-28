project(test_cgi C CXX ASM)

add_executable(test_cgi test_cgi.cpp)

target_link_libraries(test_cgi 
    WEB
	DRIVERS
) 

pico_enable_stdio_usb(test_cgi 1)
pico_enable_stdio_uart(test_cgi 0)

#Generates different file formats
pico_add_extra_outputs(test_cgi)
    