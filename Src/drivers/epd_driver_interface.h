#ifndef EPD_DRIVER_INTERFACE_H
#define EPD_DRIVER_INTERFACE_H

#include <stdint.h>
#include "hal/epd_hal_interface.h" 

typedef struct EPD_Driver_Interface {
    // Identification
    const char* name; 

    // Basic Control
    // Hardware reset
    void (*reset)(const EPD_HAL* hal);

    // Software reset
    void (*swReset)(const EPD_HAL* hal);

    void (*init)(const EPD_HAL* hal);

    // Data Write Settings
    // Set write window (Set Ram X/Y address start/end position)
    void (*set_window)(const EPD_HAL *hal, uint16_t width, uint16_t height);
    
    // Set write cursor (Set Ram X/Y address counter)
    void (*set_cursor)(const EPD_HAL* hal, uint16_t x, uint16_t y);
    
    // Prepare to write RAM (send Command 0x24 or 0x26)
    // After calling this function, the Core layer will continuously call hal->spi_write_buffer to send image data
    void (*write_ram_begin)(const EPD_HAL* hal, uint8_t color_layer);

    void (*write_ram)(const EPD_HAL* hal, const uint8_t* data, uint16_t length);

    // Refresh Control
    // Start update (Master Activate / Display Refresh)
    void (*update)(const EPD_HAL* hal);
    
    // Wait until busy (Wait Busy High/Low)
    void (*wait_busy)(const EPD_HAL *hal, uint32_t timeout_ms);

    // 5. Power Management
    // Enter deep sleep
    void (*sleep)(const EPD_HAL* hal);

    // 6. Load LUT (Optional, if IC supports custom LUT)
    void (*load_lut)(const EPD_HAL *hal, void* lutv);

} EPD_Driver_Interface;

extern const EPD_Driver_Interface SSD1680_Driver;

#endif // EPD_DRIVER_INTERFACE_H