// inc/epd_types.h

#ifndef EPD_TYPES_H
#define EPD_TYPES_H
#include "drivers/epd_driver_interface.h"
#include <stdint.h>

typedef struct {
    const char* name;          
    uint16_t width;           
    uint16_t height;
    const struct EPD_Driver_Interface* driver; 
    
    const uint8_t** lut;
    const uint32_t lut_size;
    const uint32_t lut_entry_size;
    
    uint32_t powerOnDelayMs;
    uint32_t RstDelayMs;
    uint32_t updateDelayMs;

} EPD_Profile;

typedef struct {
    const EPD_Profile* profile; 
    const EPD_HAL* hal;         
    
    uint16_t cursor_x;
    uint16_t cursor_y;
    uint8_t color_mode;
    uint8_t update_sequence_status;
} EPD_Handle;

typedef enum uint8_t {
    EPD_COLOR_MODE_BW = 0,      
    EPD_COLOR_MODE_GRAYSCALE_2B,
    EPD_COLOR_MODE_GRAYSCALE_3B,
    EPD_COLOR_MODE_GRAYSCALE_4B,
    EPD_COLOR_MODE_GRAYSCALE_5B,
    EPD_COLOR_MODE_GRAYSCALE_6B,
    EPD_COLOR_MODE_BWR,        
    EPD_COLOR_MODE_BWR_scale_2B,        
    EPD_COLOR_MODE_BWR_scale_3B,        
    EPD_COLOR_MODE_BWR_scale_4B,        
    EPD_COLOR_MODE_BWY,       
    EPD_COLOR_MODE_BWY_scale_2B,        
    EPD_COLOR_MODE_BWY_scale_3B,        
    EPD_COLOR_MODE_BWY_scale_4B,        
    EPD_COLOR_MODE_BWYR,        
    EPD_COLOR_MODE_BWYR_scale_2B,       
    EPD_COLOR_MODE_BWYR_scale_3B,       
    EPD_COLOR_MODE_BWYR_scale_4B,       
} EPD_ColorMode_t;

#endif // EPD_TYPES_H