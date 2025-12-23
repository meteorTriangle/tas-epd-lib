# stm32_auto_drivers.cmake
# Automatically selects CMSIS and HAL drivers based on STM32_TARGET_DEVICE

if(NOT DEFINED STM32_TARGET_DEVICE)
    message(FATAL_ERROR "STM32_TARGET_DEVICE is not defined. Please define it before including this file (e.g., set(STM32_TARGET_DEVICE STM32F103xB))")
endif()

# 1. Determine Family from Device Name (e.g. STM32F103xB -> F1)
string(REGEX MATCH "^STM32([FL][0-9])" FAMILY_MATCH ${STM32_TARGET_DEVICE})
if(NOT FAMILY_MATCH)
    message(FATAL_ERROR "Could not determine STM32 family from device name: ${STM32_TARGET_DEVICE}")
endif()

set(STM32_FAMILY ${CMAKE_MATCH_1}) # e.g., F1
message(STATUS "Detected STM32 Family: ${STM32_FAMILY} for device ${STM32_TARGET_DEVICE}")

# 2. Map Family to Driver Folders
# Adjust these folder names to match your actual directory structure in Drivers/
if(STM32_FAMILY STREQUAL "F0")
    set(HAL_DIR_NAME "STM32F0xx_HAL")
    set(CMSIS_DIR_NAME "CMSIS_F0")
elseif(STM32_FAMILY STREQUAL "F1")
    set(HAL_DIR_NAME "STM32F1xx_HAL")
    set(CMSIS_DIR_NAME "CMSIS_F1")
elseif(STM32_FAMILY STREQUAL "F3")
    set(HAL_DIR_NAME "STM32F3xx_HAL")
    set(CMSIS_DIR_NAME "CMSIS_F3")
elseif(STM32_FAMILY STREQUAL "F4")
    set(HAL_DIR_NAME "STM32F4xx_HAL")
    set(CMSIS_DIR_NAME "CMSIS_F4")
elseif(STM32_FAMILY STREQUAL "L1")
    set(HAL_DIR_NAME "STM32L1xx_HAL")
    set(CMSIS_DIR_NAME "CMSIS_L1")
else()
    message(FATAL_ERROR "Unsupported STM32 Family: ${STM32_FAMILY}")
endif()

# 3. Define Paths
# Assuming this file is in example/STM32_Example/cmake/
# And Drivers is in example/STM32_Example/Drivers/
get_filename_component(CURRENT_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(DRIVERS_ROOT "${CURRENT_CMAKE_DIR}/../Drivers")

set(HAL_PATH "${DRIVERS_ROOT}/${HAL_DIR_NAME}")
set(CMSIS_DEVICE_PATH "${DRIVERS_ROOT}/${CMSIS_DIR_NAME}")
set(CMSIS_CORE_PATH "${DRIVERS_ROOT}/CMSIS_5/CMSIS/Core")

# 4. Create the STM32_HAL Target
if(NOT TARGET STM32_HAL)
    add_library(STM32_HAL STATIC)

    # Add HAL Sources
    file(GLOB HAL_SOURCES "${HAL_PATH}/Src/*.c")
    # Exclude template files
    list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_template.c$")
    
    target_sources(STM32_HAL PRIVATE ${HAL_SOURCES})

    # Add Include Directories
    target_include_directories(STM32_HAL PUBLIC
        "${CMSIS_CORE_PATH}/Include"
        "${CMSIS_DEVICE_PATH}/Include"
        "${HAL_PATH}/Inc"
        "${HAL_PATH}/Inc/Legacy"
    )

    # Add Compile Definitions
    target_compile_definitions(STM32_HAL PUBLIC
        USE_HAL_DRIVER
        ${STM32_TARGET_DEVICE}
    )

    # 5. Set MCU Specific Flags
    if(STM32_FAMILY STREQUAL "F0")
        set(MCU_FLAGS -mcpu=cortex-m0 -mthumb)
    elseif(STM32_FAMILY STREQUAL "F1")
        set(MCU_FLAGS -mcpu=cortex-m3 -mthumb)
    elseif(STM32_FAMILY STREQUAL "F3")
        set(MCU_FLAGS -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb)
    elseif(STM32_FAMILY STREQUAL "F4")
        set(MCU_FLAGS -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb)
    elseif(STM32_FAMILY STREQUAL "L1")
        set(MCU_FLAGS -mcpu=cortex-m3 -mthumb)
    endif()

    target_compile_options(STM32_HAL PUBLIC ${MCU_FLAGS})
    target_link_options(STM32_HAL PUBLIC ${MCU_FLAGS})
    
    message(STATUS "Configured STM32_HAL target with drivers from ${HAL_DIR_NAME}")
endif()
