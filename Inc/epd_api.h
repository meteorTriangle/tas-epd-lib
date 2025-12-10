// inc/epd_api.h
#include "epd_types.h"

// 初始化 API：傳入 Handle, HAL, 以及 Profile
void EPD_API_Init(EPD_Handle* handle, const EPD_HAL* hal, const EPD_Profile* profile);

// void EPD_API_DeInit(EPD_Handle* handle);


// void EPD_Update(EPD_Handle* handle);