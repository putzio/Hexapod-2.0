import os


print("Write new test name:")
test_name = input()
path = f"./test_combined/{test_name}"
try:
    os.mkdir(path)
except OSError:
    print("Directory already exists")
    exit()
f = open(f"{path}/{test_name}.cpp", "a")
f.write(
    """
#include <stdio.h>
#include "pico/stdlib.h"
int main(){
    stdio_init_all();
    while(1){
        printf(\"Hello World!\\n\");
        sleep_ms(1000);
        }
    return 0;
}
"""
)
f.close()

f = open(f"{path}/CMakeLists.txt", "a")
f.write(
    f"""
include($ENV{{PICO_SDK_PATH}}/external/pico_sdk_import.cmake)
pico_sdk_init()

project({test_name} C CXX)

add_executable({test_name} {test_name}.cpp)

target_link_libraries({test_name} 
    LOGIC
    DRIVERS
    hardware_spi
) 

pico_enable_stdio_usb({test_name} 1)
pico_enable_stdio_uart({test_name} 0)

#Generates different file formats
pico_add_extra_outputs({test_name})
    """
)
f.close()

f = open(f"./test_combined/CMakeLists.txt", "a")
f.write(f"\r\nadd_subdirectory({test_name})")
