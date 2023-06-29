import os


def UpdateMainCMakesLists(path):
    dirs = os.listdir(path)
    dirs = [d for d in dirs if os.path.isdir(os.path.join(path, d))]
    print(dirs)

    with open(f"{path}/CMakeLists.txt", "w") as f:
        for dir in dirs:
            f.write(f"add_subdirectory({dir})\n")


print("Choose test type:\r\n1. System\r\n2. Hardware \r\n3. Refresh CMakeLists.txt")
test_type = input()
test_system_path = f"./test_system"
test_hardware_path = f"./test_hardware_drivers"
match test_type:
    case "1":
        path = test_system_path
        target_link_libraries = "LOGIC\n\tDRIVERS"
    case "2":
        path = test_hardware_path
        target_link_libraries = "DRIVERS"
    case "3":
        UpdateMainCMakesLists(test_system_path)
        UpdateMainCMakesLists(test_hardware_path)
        exit()
    case _:
        print("Wrong test type")
        exit()

print("Write new test name:")
test_name = input()

try:
    os.mkdir(f"{os.path.join(path,test_name)}")
except OSError:
    print("Directory already exists")
    exit()
with open(f"{path}/{test_name}/{test_name}.cpp", "w") as f:
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

with open(f"{path}/{test_name}/CMakeLists.txt", "w") as f:
    f.write(
        f"""
include($ENV{{PICO_SDK_PATH}}/external/pico_sdk_import.cmake)
pico_sdk_init()

project({test_name} C CXX)

add_executable({test_name} {test_name}.cpp)

target_link_libraries({test_name} 
    {target_link_libraries}
) 

pico_enable_stdio_usb({test_name} 1)
pico_enable_stdio_uart({test_name} 0)

#Generates different file formats
pico_add_extra_outputs({test_name})
    """
    )

UpdateMainCMakesLists(path)
