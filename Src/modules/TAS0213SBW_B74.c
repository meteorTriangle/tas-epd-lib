// src/modules/TAS0213SBW_B74.c

#include "epd_types.h"
#include "drivers/SSD1680.h"
#include "TAS0213SBW_B74.h"





const EPD_Profile EPD_PROFILE_TAS0213SBW_B74 = {
    .name = "2.13 inch Black/White(Grayscale) EPD",
    .width = 122,
    .height = 250,
    .driver = &SSD1680_Driver,
    // .lut_full = NULL,      
};