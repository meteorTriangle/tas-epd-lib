// src/modules/TAS0213SBWYR-E50.h

#include "epd_types.h"
#include "drivers/JD79661.h"
#include "TAS0213SBWYR_E50.h"


const EPD_Profile EPD_PROFILE_TAS0213SBWYR_E50 = {
    .name = "2.13 inch 4-color(B/W/Y/R) EPD",
    .width = 122,
    .height = 250,
    .driver = &JD79661_Driver,
};