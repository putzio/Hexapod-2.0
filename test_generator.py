import os

print("Choose test type:\r\n1. System\r\n2. Hardware")
test_type = input()
test_system_path = f"./test_system"
test_hardware_path = f"./test_hardware_drivers"
match test_type:
    case "1":
        path = test_system_path
    case "2":
        path = test_hardware_path
    case _:
        print("Wrong test type")
        exit()

print("Write new test name:")
test_name = input()

try:
    os.mkdir(f"{path}/{test_name}")
except OSError:
    print("Directory already exists")
    exit()
f = open(f"{path}/{test_name}/{test_name}.cpp", "a")
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

f = open(f"{path}/{test_name}/CMakeLists.txt", "a")
f.write(
    f"""
include($ENV{{PICO_SDK_PATH}}/external/pico_sdk_import.cmake)
pico_sdk_init()

project({test_name} C CXX)

add_executable({test_name} {test_name}.cpp)

target_link_libraries({test_name} 
    LOGIC
    DRIVERS
) 

pico_enable_stdio_usb({test_name} 1)
pico_enable_stdio_uart({test_name} 0)

#Generates different file formats
pico_add_extra_outputs({test_name})
    """
)
f.close()

f = open(f"{path}/{test_name}/CMakeLists.txt", "a")
f.write(f"\r\nadd_subdirectory({test_name})")
