cmake_minimum_required(VERSION 3.13...3.27)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(topdeck)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(topdeck
    src/main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(topdeck pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(topdeck)
