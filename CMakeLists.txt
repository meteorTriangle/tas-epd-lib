cmake_minimum_required(VERSION 3.22)

# 定義 Library 名稱
set(LIB_NAME TAS_EPD_Library)

# 建立 Library (INTERFACE 或 STATIC)
add_library(${LIB_NAME} STATIC)

# 1. 加入通用原始碼 (Core, Drivers, Modules)
target_sources(${LIB_NAME} PRIVATE
    # src/core/epd_core.c
    # src/core/epd_utils.c
    Src/core/epd_core.c
    Src/drivers/SSD1680.c
    Src/modules/TAS0266SBW-T90.c
    # 加入更多通用檔案...
)

# 加入 Include 路徑
target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

target_include_directories(${LIB_NAME} PUBLIC
    Src
)

# 2. 自動偵測或手動指定平台
if (PICO_SDK_PATH)
    message(STATUS "EPD Lib: Detecting Raspberry Pi Pico Build")
    target_sources(${LIB_NAME} PRIVATE src/hal/ports/hal_pico.c)
    target_link_libraries(${LIB_NAME} PUBLIC pico_stdlib hardware_spi hardware_gpio)
    
elseif (STM32_CUBE_PATH OR DEFINED STM32)
    message(STATUS "EPD Lib: Detecting STM32 Environment")
    target_link_libraries(${LIB_NAME} PRIVATE stm32cubemx)
    add_compile_definitions(STM32)
    target_sources(${LIB_NAME} PRIVATE Src/hal/ports/hal_stm32.c)
    # STM32 通常由外部負責 Link HAL，這裡只需確保編譯過
    
else()
    message(WARNING "EPD Lib: No specific platform detected, building core only.")
endif()
