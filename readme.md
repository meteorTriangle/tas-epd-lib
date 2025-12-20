# TAS EPD Library

This is a driver library for E-Paper Displays (EPDs) from TAS, designed for flexibility and portability across different microcontrollers and platforms.

## Features

* **Portable**: Easily adaptable to various platforms (STM32, Raspberry Pi Pico, Linux/Raspberry Pi, etc.) through a clean Hardware Abstraction Layer (HAL).
* **Modular**: Support for new E-Paper displays can be added by creating new module files.
* **Flexible**: Supports different display controllers and color modes.
* **CMake Integration**: Easy to integrate into existing CMake projects.

## Supported Hardware

### Platforms

* **STM32**: Integrated with STM32CubeMX generated projects.
* **Raspberry Pi Pico**: Uses Pico SDK.
* **Linux / Raspberry Pi**: Generic Linux GPIO/SPI support (e.g., via wiringPi or gpiod).
* **Custom**: User-defined HAL for any other platform.

### E-Paper Modules

* TAS0213SBW_B74
* TAS0213SBWYR-E50
* TAS0266SBW-T90
* TAS0290SBW-T94
* (More can be added in `Src/modules/`)

## Directory Structure

```
epd_lib/
├── cmake/              # CMake build scripts
│   ├── AppBuild.cmake  # For building as a standalone root project
│   └── LibBuild.cmake  # For building as a library in another project
├── example/            # Example projects (STM32, Pico, etc.)
├── Inc/                # Public API headers
├── Src/
│   ├── core/           # Core EPD logic
│   ├── drivers/        # Display controller drivers (SSD1680, JD79661, etc.)
│   ├── hal/            # Hardware Abstraction Layer interface
│   │   └── ports/      # Platform-specific HAL implementations
│   └── modules/        # Specific EPD panel configurations
└── CMakeLists.txt      # Main CMake entry point
```

## Integration Guide

### 1. Add as a Subdirectory

Add this library to your project's `CMakeLists.txt`:

```cmake
# Add the library subdirectory
add_subdirectory(path/to/epd_lib)

# Link the library to your target
target_link_libraries(YourApp PRIVATE TAS_EPD_Library)
```

### 2. Configure the Platform

Set the `TARGET_PLATFORM` variable **before** adding the subdirectory to select the correct HAL implementation:

#### STM32

```cmake
set(TARGET_PLATFORM "STM32")
add_subdirectory(epd_lib)
```

*Requires `stm32cubemx` target to be defined (standard in STM32CubeMX CMake projects).*

#### Raspberry Pi Pico

```cmake
set(TARGET_PLATFORM "PICO")
add_subdirectory(epd_lib)
```

*Requires Pico SDK environment.*

#### Linux / Raspberry Pi

```cmake
set(TARGET_PLATFORM "LINUX") # or "RPI"
add_subdirectory(epd_lib)
```

#### Custom Platform

```cmake
set(TARGET_PLATFORM "CUSTOM")
add_subdirectory(epd_lib)
```

*You must implement the HAL functions yourself and provide them to the library.*

## Usage Example

```c
#include "epd_api.h"
#include "TAS0266SBW_T90.h" // Include the specific module header

// 1. Define HAL configuration (Platform specific)
// For STM32:
// STM32_EPD_Config hal_conf = { .hspi = &hspi1, .cs_port = GPIOA, .cs_pin = GPIO_PIN_4, ... };
// EPD_HAL hal = EPD_HAL_InitSTM32(&hal_conf);

// For Custom Platform:
// EPD_HAL hal = {
//     .init = my_init,
//     .gpio_write = my_gpio_write,
//     .spi_write_byte = my_spi_write,
//     .delay_ms = my_delay,
//     ...
// };

// 2. Create EPD Handle
EPD_Handle my_epd;

void main() {
    // 3. Initialize the EPD with HAL and Profile
    EPD_API_Init(&my_epd, &hal, &EPD_PROFILE_TAS0266SBW_T90);

    // 4. Get Module Interface
    const EPD_Modules* module = &EPD_MODULE_TAS0266SBW_T90;

    // 5. Initialize Display
    module->init(&my_epd);

    // 6. Clear Display (White)
    module->clear(&my_epd, 0xFF); 

    // 7. Draw Image (if available)
    // module->write_image(&my_epd, image_buffer);

    // 8. Refresh Display
    module->update(&my_epd);
    
    while(1);
}
```

## How to Add a New Display Module

1. **Driver**: If the display uses a new controller, add the driver in `Src/drivers/`.
2. **Module**: Create `MyDisplay.c` and `MyDisplay.h` in `Src/modules/`.
    * Define `EPD_Profile` (resolution, colors, LUTs).
    * Implement `EPD_Modules` functions (init, clear, update).
3. **Build**: Ensure the new files are included in `cmake/LibBuild.cmake` (or added automatically if using glob).

## License

[License Information Here]
