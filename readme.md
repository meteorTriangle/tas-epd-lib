# TAS EPD Library

This is a driver library for E-Paper Displays (EPDs) from TAS, designed for flexibility and portability across different microcontrollers.

## Features

* **Portable**: Easily adaptable to various platforms (Arduino, STM32, Raspberry Pi Pico, etc.) through a clean Hardware Abstraction Layer (HAL).
* **Modular**: Support for new E-Paper displays can be added by creating new module files.
* **Flexible**: Supports different display controllers and color modes.

## Supported Hardware

### Platforms

* Raspberry Pi Pico
* STM32
* Arduino

### E-Paper Modules

* TAS0266SBW-T90
* TAS0426HBW-M01

## Architecture

The library is structured into three main layers:

1. **API Layer** (`Inc/epd_api.h`): Provides high-level functions to control the EPD.
2. **Core Layer** (`Src/core`): Implements the main logic for display control.
3. **Hardware Abstraction Layer (HAL)** (`Src/hal`): Defines the interface for hardware-specific functions (SPI, GPIO, delay).

The key data structures are:

* `EPD_Handle`: Represents an E-Paper display instance, linking the profile and HAL.
* `EPD_Profile`: Defines the properties of a specific E-Paper display module.
* `EPD_HAL`: A set of function pointers for hardware-specific operations.

## Getting Started

Here is a basic example of how to use the library:

```c
#include "epd_api.h"
#include "hal_stm32.h" // Your platform-specific HAL
#include "TAS0266SBW_T90.h" // The EPD module you are using

// 1. Create a handle for the EPD
EPD_Handle my_epd;

// 2. Define the HAL functions for your platform
const EPD_HAL my_hal = {
    .init = hal_stm32_init,
    .gpio_write = hal_stm32_gpio_write,
    .gpio_read = hal_stm32_gpio_read,
    .spi_write_byte = hal_stm32_spi_write_byte,
    .spi_write_buffer = hal_stm32_spi_write_buffer,
    .delay_ms = hal_stm32_delay_ms,
    .user_data = NULL, // Optional user data
};

void main() {
    // 3. Initialize the EPD
    EPD_API_Init(&my_epd, &my_hal, &EPD_PROFILE_TAS0266SBW_T90);

    // 4. Get the display-specific functions
    const EPD_Modules* epd_module = &EPD_MODULE_TAS0266SBW_T90;

    // 5. Initialize the display
    epd_module->init(&my_epd);

    // 6. Write image data to the display
    // (Image data format depends on the display and color mode)
    // epd_module->write_image(&my_epd, image_data, image_data_length);
    
    // 7. Update the display
    epd_module->update(&my_epd);
}
```

## How to Add a New Display

1. **Create a driver file** (e.g., `MyEPD.c`) in `Src/drivers/` if a new display controller is used.
2. **Create a module file** (e.g., `MyModule.c` and `MyModule.h`) in `Src/modules/`.
3. In `MyModule.h`, declare the `EPD_Profile` and `EPD_Modules` for your display.
4. In `MyModule.c`, define the `EPD_Profile` with the display's properties and the `EPD_Modules` with the corresponding functions.
5. Include `MyModule.h` in your application and use its profile and modules.

## Building the Library

This project uses CMake for building the library. You can configure the build by setting the platform-specific variables (e.g., `PICO_SDK_PATH` for Raspberry Pi Pico).
