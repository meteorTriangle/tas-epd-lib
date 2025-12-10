// inc/epd_hal_interface.h

#ifndef EPD_HAL_INTERFACE_H
#define EPD_HAL_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>


#define EPD_PIN_CS      0
#define EPD_PIN_DC      1
#define EPD_PIN_RESET   2
#define EPD_PIN_BUSY    3

typedef struct {
    // pointer to the environment-specific I/O configuration data
    void *user_data; 

    // initial(option)
    void (*init)(const void *ctx);
    
    // GPIO control
    void (*gpio_write)(const void *ctx, int pin_index, bool state);
    bool (*gpio_read)(const void *ctx, int pin_index);

    // SPI interface
    void (*spi_write_byte)(const void *ctx, uint8_t data);
    void (*spi_write_buffer)(const void *ctx, const uint8_t* data, uint32_t len);

    void (*delay_ms)(const void *ctx, uint32_t ms);
} EPD_HAL;

#endif // EPD_HAL_INTERFACE_H