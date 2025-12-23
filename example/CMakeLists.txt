cmake_minimum_required(VERSION 3.22)

set(Example_For_Pico_Dir 
    "${CMAKE_CURRENT_LIST_DIR}/Pico_Example" 
)
set(Example_For_STM32_Dir 
    "${CMAKE_CURRENT_LIST_DIR}/STM32F103C8_TAS0213SBWYR_E50"
    "${CMAKE_CURRENT_LIST_DIR}/STM32_Example"
    # "${CMAKE_CURRENT_LIST_DIR}/STM32F103C8_4CEPD_section"
)

# 根據根目錄偵測到的平台變數，決定加入哪個範例
if ("${TARGET_PLATFORM}" STREQUAL "PICO")
    message(STATUS "Example: Building for Raspberry Pi Pico")
    add_subdirectory(Pico_Example) 
    
elseif ("${TARGET_PLATFORM}" STREQUAL "STM32")
    message(STATUS "Example: Building for STM32")
    # 加入現有的 STM32 範例
    foreach(dir IN LISTS Example_For_STM32_Dir)
        add_subdirectory(${dir})
    endforeach()
else()
    # Fallback
    if (PICO_SDK_PATH)
        message(STATUS "Example: Building for Raspberry Pi Pico (Legacy)")
    elseif (STM32_CUBE_PATH OR DEFINED STM32)
        message(STATUS "Example: Building for STM32 (Legacy)")
        foreach(dir IN LISTS Example_For_STM32_Dir)
            add_subdirectory(${dir})
        endforeach()
    else()
        message(STATUS "Example: No specific platform detected, skipping examples.")
    endif()
endif()