// src/modules/TAS0290SBW_T94.c

#include "epd_types.h"
#include "drivers/SSD1680.h"
#include "TAS0290SBW_T94.h"




const EPD_Profile EPD_PROFILE_TAS0290SBW_T94 = {
    .name = "2.90 inch Black/White(Grayscale) EPD",
    .width = 128,
    .height = 296,
    .driver = &SSD1680_Driver,
};