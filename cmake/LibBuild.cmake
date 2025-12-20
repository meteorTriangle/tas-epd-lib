# Initialize Pico SDK if targeting Pico
if ("${TARGET_PLATFORM}" STREQUAL "PICO")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/pico_sdk_import.cmake)
    pico_sdk_init()
endif()

# 定義 Library 名稱
set(LIB_NAME TAS_EPD_Library)

# 建立 Library (INTERFACE 或 STATIC)
add_library(${LIB_NAME} STATIC)


# 1. 加入通用原始碼 (Core, Drivers, Modules)
target_sources(${LIB_NAME} PRIVATE
    Src/core/epd_core.c
    Src/drivers/SSD1680.c
    Src/drivers/JD79661.c
    ${MODULES}
)

# 加入 Include 路徑
target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

target_include_directories(${LIB_NAME} PUBLIC
    Src
)

# 2. 自動偵測或手動指定平台
if ("${TARGET_PLATFORM}" STREQUAL "PICO")
    message(STATUS "EPD Lib: Configuring for Raspberry Pi Pico")
    target_sources(${LIB_NAME} PRIVATE Src/hal/ports/hal_pico.c)
    target_link_libraries(${LIB_NAME} PUBLIC pico_stdlib hardware_spi hardware_gpio)

elseif ("${TARGET_PLATFORM}" STREQUAL "STM32")
    message(STATUS "EPD Lib: Configuring for STM32")
    add_compile_definitions(STM32=1)
    target_sources(${LIB_NAME} INTERFACE Src/hal/ports/hal_stm32.c)
    
    if(TARGET stm32cubemx)
        target_link_libraries(${LIB_NAME} PRIVATE stm32cubemx)
    endif()

elseif ("${TARGET_PLATFORM}" STREQUAL "LINUX" OR "${TARGET_PLATFORM}" STREQUAL "RPI")
    message(STATUS "EPD Lib: Configuring for Linux/Raspberry Pi")
    add_compile_definitions(LINUX_HAL=1)
    target_sources(${LIB_NAME} PRIVATE Src/hal/ports/hal_rpi.c)

elseif ("${TARGET_PLATFORM}" STREQUAL "CUSTOM")
    message(STATUS "EPD Lib: Configuring for User Custom HAL")
    add_compile_definitions(CUSTOM_HAL=1)

else()
    # Fallback for backward compatibility or auto-detection
    if (PICO_SDK_PATH)
        message(STATUS "EPD Lib: Detecting Raspberry Pi Pico Build (Legacy)")
        target_sources(${LIB_NAME} INTERFACE Src/hal/ports/hal_pico.c)
        target_link_libraries(${LIB_NAME} PUBLIC pico_stdlib hardware_spi hardware_gpio)
    elseif (STM32_CUBE_PATH OR DEFINED STM32)
        message(STATUS "EPD Lib: Detecting STM32 Environment (Legacy)")
        target_link_libraries(${LIB_NAME} PRIVATE stm32cubemx)
        add_compile_definitions(STM32=1)
        target_sources(${LIB_NAME} INTERFACE Src/hal/ports/hal_stm32.c)
    else()
        message(WARNING "EPD Lib: No specific platform detected, building core only.")
    endif()
endif()
