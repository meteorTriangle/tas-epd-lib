// src/hal/ports/hal_arduino.h
#ifndef HAL_ARDUINO_H
#define HAL_ARDUINO_H

#include <Arduino.h>
#include <SPI.h>
#include "epd_hal_interface.h" 

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    SPIClass *spi; 
    
    int pin_cs;
    int pin_dc;
    int pin_rst;
    int pin_busy;
    
} Arduino_EPD_Config;

EPD_HAL EPD_HAL_InitArduino(Arduino_EPD_Config *config);

#ifdef __cplusplus
}
#endif

#endif // HAL_ARDUINO_H