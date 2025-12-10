// inc/epd_types.h

#ifndef EPD_TYPES_H
#define EPD_TYPES_H
#include "drivers/epd_driver_interface.h"
#include <stdint.h>
// 前向宣告，避免循環引用
struct EPD_Driver_Interface; 

typedef struct {
    const char* name;          // 模組名稱 (Debug用)
    uint16_t width;            // 寬度
    uint16_t height;           // 高度
    // 關鍵：這個模組是用哪顆 Driver IC？
    const struct EPD_Driver_Interface* driver; 
    
    // 該模組特定的 LUT (如果是 NULL 則用 IC 內建)
    const uint8_t** lut;
    const uint32_t lut_size;
    const uint32_t lut_entry_size;
} EPD_Profile;

// 定義 Handle (操作控制代碼)
typedef struct {
    const EPD_Profile* profile; // [關鍵] 指向該螢幕的規格書
    const EPD_HAL* hal;         // 指向該螢幕連接的硬體腳位 (SPI/GPIO)
    
    // 執行時期狀態 (Runtime State)
    uint16_t cursor_x;
    uint16_t cursor_y;
    uint8_t color_mode;
    uint8_t update_sequence_status;
} EPD_Handle;

// EPD Top level function
typedef struct {
    void (*init)(EPD_Handle* handle);
    void (*write_image)(EPD_Handle* handle, const uint8_t* image_data, uint32_t data_length);
    void (*update)(EPD_Handle* handle);
    // void (*deinit)(EPD_Handle* handle);
    // void (*clear)(EPD_Handle* handle);
    // void (*display_frame)(EPD_Handle* handle, const uint8_t* frame_buffer);
    // void (*display_frame_partial)(EPD_Handle* handle, const uint8_t* frame_buffer, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    // void (*sleep)(EPD_Handle* handle);
    // void (*set_lut)(EPD_Handle* handle, const uint8_t** lut, size_t lut_size, size_t lut_entry_size);
    // void (*set_color_mode)(EPD_Handle* handle, uint8_t mode);
    // uint8_t (*get_color_mode)(EPD_Handle* handle);
    // void (*set_cursor)(EPD_Handle* handle, uint16_t x, uint16_t y);
    // void (*get_cursor)(EPD_Handle* handle, uint16_t* x, uint16_t* y);
    // void (*draw_pixel)(EPD_Handle* handle, uint16_t x, uint16_t y, uint8_t color);
    // void (*draw_hline)(EPD_Handle* handle, uint16_t x, uint16_t y, uint16_t width, uint8_t color);
    // void (*draw_vline)(EPD_Handle* handle, uint16_t x, uint16_t y, uint16_t height, uint8_t color);
    // void (*draw_rect)(EPD_Handle* handle, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
    // void (*fill_rect)(EPD_Handle* handle, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
    // void (*draw_bitmap)(EPD_Handle* handle, const uint8_t* bitmap, uint16_t width, uint16_t height, uint8_t color);
    // void (*draw_bitmap_partial)(EPD_Handle* handle, const uint8_t* bitmap, uint16_t width, uint16_t height, uint8_t color, uint16_t x, uint16_t y);
} EPD_Modules;

typedef enum uint8_t {
    EPD_COLOR_MODE_BW = 0,      // 黑白
    EPD_COLOR_MODE_GRAYSCALE_2B,   // 灰階
    EPD_COLOR_MODE_GRAYSCALE_3B,   // 灰階
    EPD_COLOR_MODE_GRAYSCALE_4B,   // 灰階
    EPD_COLOR_MODE_GRAYSCALE_5B,   // 灰階
    EPD_COLOR_MODE_GRAYSCALE_6B,   // 灰階
    EPD_COLOR_MODE_BWR,        // 黑白紅
    EPD_COLOR_MODE_BWR_scale_2B,        // 黑白紅 (2B)
    EPD_COLOR_MODE_BWR_scale_3B,        // 黑白紅 (3B)
    EPD_COLOR_MODE_BWR_scale_4B,        // 黑白紅 (4B)
    EPD_COLOR_MODE_BWY,        // 黑白黃
    EPD_COLOR_MODE_BWY_scale_2B,        // 黑白黃 (2B)
    EPD_COLOR_MODE_BWY_scale_3B,        // 黑白黃 (3B)
    EPD_COLOR_MODE_BWY_scale_4B,        // 黑白黃 (4B)
    EPD_COLOR_MODE_BWYR,        // 黑白黃紅
    EPD_COLOR_MODE_BWYR_scale_2B,        // 黑白黃紅 (2B)
    EPD_COLOR_MODE_BWYR_scale_3B,        // 黑白黃紅 (3B)
    EPD_COLOR_MODE_BWYR_scale_4B,        // 黑白黃紅 (4B)
} EPD_ColorMode_t;

#endif // EPD_TYPES_H