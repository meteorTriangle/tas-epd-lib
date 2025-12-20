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
    
    // After calling this function, the Core layer will continuously call hal->spi_write_buffer to send image data
    void (*write_ram_begin)(const EPD_HAL* hal, uint8_t color_layer);

    void (*write_ram_end)(const EPD_HAL* hal);

    void (*write_ram)(const EPD_HAL* hal, const uint8_t* data, uint32_t length);

    // Refresh Control
    // Start update (Master Activate / Display Refresh)
    void (*update)(const EPD_HAL* hal);
    
    /**
     * @brief 
     * Wait until the display is idle (not busy)
     * @param hal Pointer to the EPD_HAL structure
     * @param timeout_ms Maximum time to wait in milliseconds
     * @return uint8_t EPD_OK if successful, EPD_ERROR_TIMEOUT if timeout occurs
     */
    uint8_t (*wait_busy)(const EPD_HAL *hal, uint32_t timeout_ms);

    // 5. Power Management
    // Enter deep sleep
    void (*sleep)(const EPD_HAL* hal);

    // 6. Load LUT (Optional, if IC supports custom LUT)
    void (*load_lut)(const EPD_HAL *hal, void* lutv);

} EPD_Driver_Interface;

#endif // EPD_DRIVER_INTERFACE_H