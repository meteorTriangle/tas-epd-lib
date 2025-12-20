// src/hal/ports/hal_stm32.h

#ifndef HAL_STM32_H
#define HAL_STM32_H

#include "main.h"
#include "../epd_hal_interface.h"


typedef struct {
    SPI_HandleTypeDef *hspi; 
    
    GPIO_TypeDef* cs_port;
    uint16_t      cs_pin;
    
    GPIO_TypeDef* dc_port;
    uint16_t      dc_pin;
    
    GPIO_TypeDef* rst_port;
    uint16_t      rst_pin;
    
    GPIO_TypeDef* busy_port;
    uint16_t      busy_pin;
} STM32_EPD_Config;

EPD_HAL EPD_HAL_InitSTM32(STM32_EPD_Config *config);

#endif