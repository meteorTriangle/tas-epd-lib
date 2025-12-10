// src/hal/ports/hal_pico.h
#ifndef HAL_PICO_H
#define HAL_PICO_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "epd_hal_interface.h" // 引用你的通用介面

// 定義 Pico 專用的硬體設定
typedef struct {
    // SPI 實例：傳入 spi0 或 spi1
    spi_inst_t *spi; 
    
    // GPIO 編號 (例如 17, 20 等，不是 Pin 腳位號)
    uint8_t pin_cs;
    uint8_t pin_dc;
    uint8_t pin_rst;
    uint8_t pin_busy;
    
} Pico_EPD_Config;

// 初始化函式宣告
EPD_HAL EPD_HAL_InitPico(Pico_EPD_Config *config);

#endif // HAL_PICO_H