set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
endif()
if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
endif()
if(NOT DEFINED CMAKE_ASM_COMPILER)
    set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
endif()

set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Default to Cortex-M3 if not specified (can be overridden)
if(NOT DEFINED MCU_FLAGS)
    set(MCU_FLAGS "-mcpu=cortex-m3 -mthumb")
endif()

set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -Wextra -fdata-sections -ffunction-sections" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -Wall -Wextra -fno-rtti -fno-exceptions -fdata-sections -ffunction-sections" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -Wl,--gc-sections --specs=nano.specs" CACHE STRING "" FORCE)
