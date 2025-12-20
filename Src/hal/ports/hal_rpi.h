#ifndef HAL_RPI_H
#define HAL_RPI_H

#include "../epd_hal_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int spi_channel; // 0 or 1
    int cs_pin;
    int dc_pin;
    int rst_pin;
    int busy_pin;
} RPI_EPD_Config;

EPD_HAL EPD_HAL_InitRPI(RPI_EPD_Config *config);

#ifdef __cplusplus
}
#endif

#endif // HAL_RPI_H
