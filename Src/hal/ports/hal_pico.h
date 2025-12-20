// src/hal/ports/hal_pico.h
#ifndef HAL_PICO_H
#define HAL_PICO_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "epd_hal_interface.h"

typedef struct {
    spi_inst_t *spi; 
    
    uint8_t pin_cs;
    uint8_t pin_dc;
    uint8_t pin_rst;
    uint8_t pin_busy;
    
} Pico_EPD_Config;

EPD_HAL EPD_HAL_InitPico(Pico_EPD_Config *config);

#endif // HAL_PICO_H