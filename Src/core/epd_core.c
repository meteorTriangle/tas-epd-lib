// src/core/epd_core.c

#include "epd_api.h"
#include <string.h>

void EPD_API_Init(EPD_Handle* handle, const EPD_HAL* hal, const EPD_Profile* profile){
    handle->cursor_x = 0;
    handle->cursor_y = 0;
    handle->color_mode = 0;
    handle->update_sequence_status = 0;
    handle->hal = hal;
    handle->profile = profile;
}