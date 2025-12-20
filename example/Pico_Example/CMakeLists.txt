cmake_minimum_required(VERSION 3.22)

project(Pico_Example C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize Pico SDK (if not already done by root)
if (NOT TARGET pico_stdlib)
    include(../../cmake/pico_sdk_import.cmake)
    pico_sdk_init()
endif()

add_executable(Pico_Example
    main.c
)

# Link EPD Library and Pico SDK
target_link_libraries(Pico_Example PRIVATE
    TAS_EPD_Library
    pico_stdlib
    hardware_spi
    hardware_gpio
)

# Enable USB/UART output
pico_enable_stdio_usb(Pico_Example 1)
pico_enable_stdio_uart(Pico_Example 0)

pico_add_extra_outputs(Pico_Example)
