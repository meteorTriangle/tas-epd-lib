// src/modules/TAS0266SBW-T90.c

#include "epd_types.h"
#include "drivers/SSD1680.h"
#include "TAS0266SBW_T90.h"





const EPD_Profile EPD_PROFILE_TAS0266SBW_T90 = {
    .name = "2.66 inch Black/White(Grayscale) EPD",
    .width = 152,
    .height = 296,
    .driver = &SSD1680_Driver,
    // .lut_full = NULL,      
};