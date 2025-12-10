// src/hal/ports/hal_arduino.cpp

#if defined(ARDUINO)
#include "hal_arduino.h"

// 定義 SPI 參數 (通常電子紙跑 4MHz, MSB First, Mode 0)
static const SPISettings epd_spi_settings(4000000, MSBFIRST, SPI_MODE0);

// --- 實作細節 ---

static void ard_gpio_write(const void *ctx, int pin_index, bool state) {
    const Arduino_EPD_Config *cfg = (const Arduino_EPD_Config *)ctx;
    int pin = -1;
    
    switch (pin_index) {
        case EPD_PIN_CS:    pin = cfg->pin_cs; break;
        case EPD_PIN_DC:    pin = cfg->pin_dc; break;
        case EPD_PIN_RESET: pin = cfg->pin_rst; break;
    }
    
    if (pin != -1) {
        digitalWrite(pin, state ? HIGH : LOW);
    }
}

static bool ard_gpio_read(const void *ctx, int pin_index) {
    const Arduino_EPD_Config *cfg = (const Arduino_EPD_Config *)ctx;
    if (pin_index == EPD_PIN_BUSY) {
        return digitalRead(cfg->pin_busy) == HIGH; // 或根據 BUSY 邏輯調整
    }
    return false;
}

static void ard_spi_write_byte(const void *ctx, uint8_t data) {
    const Arduino_EPD_Config *cfg = (const Arduino_EPD_Config *)ctx;
    
    // 使用 Transaction 確保與其他 SPI 裝置共存時設定正確
    cfg->spi->beginTransaction(epd_spi_settings);
    cfg->spi->transfer(data);
    cfg->spi->endTransaction();
}

static void ard_spi_write_buffer(const void *ctx, const uint8_t* data, uint32_t len) {
    const Arduino_EPD_Config *cfg = (const Arduino_EPD_Config *)ctx;
    
    // 針對大量資料，Transaction 包在迴圈外面效率較高
    cfg->spi->beginTransaction(epd_spi_settings);
    // Arduino 的 transfer 也可以傳 buffer，但依版本不同，這裡用迴圈最通用
    for (uint32_t i = 0; i < len; i++) {
        cfg->spi->transfer(data[i]);
    }
    cfg->spi->endTransaction();
}

static void ard_delay(const void *ctx, uint32_t ms) {
    (void)ctx;
    delay(ms);
}

// 內部初始化：設定 pinMode
static void ard_internal_init(const void *ctx) {
    const Arduino_EPD_Config *cfg = (const Arduino_EPD_Config *)ctx;
    
    pinMode(cfg->pin_cs, OUTPUT);
    pinMode(cfg->pin_dc, OUTPUT);
    pinMode(cfg->pin_rst, OUTPUT);
    pinMode(cfg->pin_busy, INPUT); 
    
    // 預設狀態
    digitalWrite(cfg->pin_cs, HIGH);
}

// --- 建構子 ---

EPD_HAL EPD_HAL_InitArduino(Arduino_EPD_Config *config) {
    EPD_HAL hal;
    hal.user_data = (void*)config; // 將 C++ 的 struct 指標轉為 void*
    
    hal.init = ard_internal_init;
    hal.gpio_write = ard_gpio_write;
    hal.gpio_read = ard_gpio_read;
    hal.spi_write_byte = ard_spi_write_byte;
    hal.spi_write_buffer = ard_spi_write_buffer;
    hal.delay_ms = ard_delay;
    
    return hal;
}

#endif // ARDUINO