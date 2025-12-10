// src/hal/ports/hal_stm32.h

#ifndef HAL_STM32_H
#define HAL_STM32_H

#include "main.h" // 包含 STM32 HAL 定義
#include "hal/epd_hal_interface.h"


// 定義一個結構來存「這塊模組用的硬體資源」
typedef struct {
    SPI_HandleTypeDef *hspi; // 關鍵：可以存 &hspi1, &hspi2...
    
    // 定義各個腳位的 Port 和 Pin
    GPIO_TypeDef* cs_port;
    uint16_t      cs_pin;
    
    GPIO_TypeDef* dc_port;
    uint16_t      dc_pin;
    
    GPIO_TypeDef* rst_port;
    uint16_t      rst_pin;
    
    GPIO_TypeDef* busy_port;
    uint16_t      busy_pin;
} STM32_EPD_Config;

// 宣告初始化函式，回傳綁定好的 HAL 物件
EPD_HAL EPD_HAL_InitSTM32(STM32_EPD_Config *config);

#endif