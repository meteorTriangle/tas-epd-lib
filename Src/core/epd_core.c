// src/core/epd_core.c

#include "epd_api.h"
#include <string.h>

uint8_t handlePtrNullCheck(const EPD_Handle* handle){
    if( handle == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->hal == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->profile == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->profile->driver == NULL ){
        return EPD_ERROR_DRIVER;
    }
    return EPD_OK;
}

uint8_t EPD_API_Init(EPD_Handle* handle, const EPD_HAL* hal, const EPD_Profile* profile){
    if ( handle == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( profile == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( hal == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    handle->cursor_x = 0;
    handle->cursor_y = 0;
    handle->color_mode = 0;
    handle->update_sequence_status = 0;
    handle->hal = hal;
    handle->profile = profile;
    return EPD_OK;
}

uint8_t EPD_Init(EPD_Handle* handle){
    if( handle == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->hal == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->profile == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->profile->driver == NULL ){
        return EPD_ERROR_DRIVER;
    }

    if( handle->profile->driver->reset == NULL ||
        handle->profile->driver->swReset == NULL ||
        handle->profile->driver->wait_busy == NULL ){
        return EPD_ERROR_NOT_SUPPORTED;
    }
    handle->profile->driver->reset(handle->hal);
    handle->profile->driver->wait_busy(handle->hal, 1000);
    handle->profile->driver->swReset(handle->hal);
    handle->profile->driver->wait_busy(handle->hal, 1000);
    
    if( handle->profile->driver->init != NULL ){
        handle->profile->driver->init(handle->hal);
    }
    handle->profile->driver->wait_busy(handle->hal, 1000);

    // set window
    if( handle->profile->driver->set_window != NULL ){
        handle->profile->driver->set_window(handle->hal, handle->profile->width, handle->profile->height);
    }
    // set cursor
    if( handle->profile->driver->set_cursor != NULL ){
        handle->profile->driver->set_cursor(handle->hal, 0, 0);
    }
    return EPD_OK;
}

uint8_t EPD_setCursor(EPD_Handle* handle, uint16_t x, uint16_t y){
    if( handle == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->profile == NULL || handle->profile->driver == NULL ){
        return EPD_ERROR_DRIVER;
    }
    if( handle->profile->driver->set_cursor == NULL ){
        return EPD_ERROR_NOT_SUPPORTED;
    }
    handle->cursor_x = x;
    handle->cursor_y = y;
    if( handle->profile->driver->set_cursor == NULL ){
        return EPD_ERROR_NOT_SUPPORTED;
    }
    handle->profile->driver->set_cursor(handle->hal, x, y);
    return EPD_OK;
}

uint8_t EPD_WriteImage(EPD_Handle* handle, const uint8_t* image_data, uint32_t data_length, uint8_t color_layer){
    if( handlePtrNullCheck(handle) != EPD_OK ){
        return EPD_ERROR_NULL_PTR;
    }
    if( image_data == NULL ){
        return EPD_ERROR_NULL_PTR;
    }
    if ( data_length == 0 ){
        return EPD_ERROR_INVALID_PARAM;
    }
    // begin write
    if( handle->profile->driver->write_ram_begin == NULL ){
        return EPD_ERROR_NOT_SUPPORTED;
    }
    handle->profile->driver->write_ram_begin(handle->hal, color_layer);
    // write image data
    if( handle->profile->driver->write_ram == NULL ){
        return EPD_ERROR_NOT_SUPPORTED;
    }
    handle->profile->driver->write_ram(handle->hal, image_data, data_length);
    // end write
    if( handle->profile->driver->write_ram_end != NULL ){
        handle->profile->driver->write_ram_end(handle->hal);
    }
    return EPD_OK;
}

uint8_t EPD_Update(EPD_Handle* handle){
    if( handlePtrNullCheck(handle) != EPD_OK ){
        return EPD_ERROR_NULL_PTR;
    }
    if( handle->profile->driver->update == NULL ){
        return EPD_ERROR_NOT_SUPPORTED;
    }
    handle->profile->driver->update(handle->hal);
    return EPD_OK;
}