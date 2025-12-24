// src/modules/TAS0426SBW_T82.c

#include "epd_types.h"
#include "drivers/SSD1677.h"
#include "TAS0426SBW_T82.h"



const EPD_Profile EPD_PROFILE_TAS0426SBW_T82 = {
    .name = "4.26 inch Black/White(Grayscale) EPD",
    .width = 800,
    .height = 680,
    .driver = &SSD1677_Driver,
};