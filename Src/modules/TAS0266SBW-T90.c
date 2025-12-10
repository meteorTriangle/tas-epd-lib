// src/modules/TAS0266SBW-T90.c

#include "epd_types.h"
#include "drivers/SSD1680.h"
#include "TAS0266SBW_T90.h"


static void initialize_TAS0266SBW_T90(EPD_Handle* handle) {
    handle->profile->driver->reset(handle->hal);
    handle->profile->driver->wait_busy(handle->hal, 1000);
    handle->profile->driver->swReset(handle->hal);
    handle->profile->driver->set_window(handle->hal, handle->profile->width, handle->profile->height);
    handle->profile->driver->set_cursor(handle->hal, 0, 0);
}

static void update_lut_TAS0266SBW_T90(EPD_Handle* handle, uint8_t sequence) {
    // switch (sequence) {
    //     case 0:
    //         // Full update LUT
    //         // do nothing, use built-in LUT
    //         break;
    //     case 1:
    //         // Partial update LUT
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_PARTIAL);
    //         break;
    //     case 2:
    //         // Fast update LUT
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_FAST);
    //         break;
    //     case 3:
    //         // Grayscale update LUT for 2-bit seq1 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_2BIT_SEQ1);
    //         break;
    //     case 4:
    //         // Grayscale update LUT for 2-bit seq2 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_2BIT_SEQ2);
    //         break;
    //     case 5:
    //         // Grayscale update LUT for 3-bit seq1 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_3BIT_SEQ1);
    //         break;
    //     case 6:
    //         // Grayscale update LUT for 3-bit seq2 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_3BIT_SEQ2);
    //         break;
    //     case 7:
    //         // Grayscale update LUT for 3-bit seq3 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_3BIT_SEQ3);
    //         break;
    //     case 8:
    //         // Grayscale update LUT for 4-bit seq1 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_4BIT_SEQ1);
    //         break;
    //     case 9:
    //         // Grayscale update LUT for 4-bit seq2 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_4BIT_SEQ2);
    //         break;
    //     case 10:
    //         // Grayscale update LUT for 4-bit seq3 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_4BIT_SEQ3);
    //         break;
    //     case 11:
    //         // Grayscale update LUT for 4-bit seq4 mode
    //         handle->profile->driver->load_lut(handle->hal, (void*)LUT_TAS0266SBW_T90_GRAYSCALE_4BIT_SEQ4);
    //         break;
    //     default:
    //         break;
    // }
}

static void write_image_TAS0266SBW_T90(EPD_Handle* handle, const uint8_t* image_data, uint32_t data_length) {
    handle->profile->driver->write_ram_begin(handle->hal, SSD1680_WRITE_RAM1);
    handle->profile->driver->write_ram(handle->hal, image_data, data_length);
}

static void update_TAS0266SBW_T90(EPD_Handle* handle) {
    handle->profile->driver->update(handle->hal);
}



const EPD_Modules EPD_MODULE_TAS0266SBW_T90 = {
    .init = initialize_TAS0266SBW_T90,
    // .update_lut = update_lut_TAS0266SBW_T90,
    .write_image = write_image_TAS0266SBW_T90,
    .update = update_TAS0266SBW_T90,
};


const EPD_Profile EPD_PROFILE_TAS0266SBW_T90 = {
    .name = "2.66 inch Black/White(Grayscale) EPD",
    .width = 152,
    .height = 296,
    .driver = &SSD1680_Driver, // 指向 SSD1680 的驅動表
    // .lut_full = NULL,          // 假設使用 IC 內建 LUT
};