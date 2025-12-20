cmake_minimum_required(VERSION 3.22)

# 根據根目錄偵測到的平台變數，決定加入哪個範例
if ("${TARGET_PLATFORM}" STREQUAL "PICO")
    message(STATUS "Example: Building for Raspberry Pi Pico")
    add_subdirectory(Pico_Example) 
    
elseif ("${TARGET_PLATFORM}" STREQUAL "STM32")
    message(STATUS "Example: Building for STM32")
    # 加入現有的 STM32 範例
    add_subdirectory(STM32F103C8_TAS0213SBWYR_E50)
    
else()
    # Fallback
    if (PICO_SDK_PATH)
        message(STATUS "Example: Building for Raspberry Pi Pico (Legacy)")
    elseif (STM32_CUBE_PATH OR DEFINED STM32)
        message(STATUS "Example: Building for STM32 (Legacy)")
        add_subdirectory(STM32F103C8_TAS0213SBWYR_E50)
    else()
        message(STATUS "Example: No specific platform detected, skipping examples.")
    endif()
endif()