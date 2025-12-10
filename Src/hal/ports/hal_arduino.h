// src/hal/ports/hal_arduino.h
#ifndef HAL_ARDUINO_H
#define HAL_ARDUINO_H

#include <Arduino.h>
#include <SPI.h>
#include "epd_hal_interface.h" // 引用你的 C 語言介面

// 確保 C 語言連結兼容性
#ifdef __cplusplus
extern "C" {
#endif

// 定義 Arduino 的硬體設定
typedef struct {
    // 支援傳入 &SPI 或 &SPI1 (ESP32/STM32 Arduino Core)
    SPIClass *spi; 
    
    // 定義 Pin 腳位 (Arduino 使用 int 或 int8_t)
    int pin_cs;
    int pin_dc;
    int pin_rst;
    int pin_busy;
    
} Arduino_EPD_Config;

// 初始化函式
EPD_HAL EPD_HAL_InitArduino(Arduino_EPD_Config *config);

#ifdef __cplusplus
}
#endif

#endif // HAL_ARDUINO_H