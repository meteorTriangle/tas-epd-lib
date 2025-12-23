cmake_minimum_required(VERSION 3.22)

# 1. 設定目標晶片型號 (必須在 include 之前設定)
set(STM32_TARGET_DEVICE "STM32F103xB")

set(CMAKE_PROJECT_NAME STM32F103C8_2CEPD_section)

# 2. 引入自動判斷腳本
# 假設您的專案在 example/STM32_Example/xxx_Project/ 下，腳本在 example/STM32_Example/cmake/ 下
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/stm32_auto_drivers.cmake)

# 3. 定義您的專案
project(${CMAKE_PROJECT_NAME} C ASM)

# 4. 加入您的原始碼
add_executable(${CMAKE_PROJECT_NAME}
    Core/Src/main.c
    Core/Src/stm32f1xx_it.c
    Core/Src/stm32f1xx_hal_msp.c
    Core/Src/system_stm32f1xx.c
    startup_stm32f103xb.s
)

# 5. 設定 Include 路徑 (您的 Core/Inc)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    Core/Inc
)

# 6. 連結自動產生的 STM32_HAL
target_include_directories(STM32_HAL PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    STM32_HAL
    TAS_EPD_Library
)

# 7. 設定 Linker Script
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/STM32F103XX_FLASH.ld
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
)

# 8. 產生 Hex 和 Bin 檔案
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Building ${CMAKE_PROJECT_NAME}.hex and ${CMAKE_PROJECT_NAME}.bin"
)
