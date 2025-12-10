// src/hal/ports/hal_stm32.c

#include "hal_stm32.h"
#ifdef STM32

// 實作 SPI 寫入
static void stm32_spi_write_byte(const void *ctx, uint8_t data) {
    // 1. 將通用的 void* 轉回 STM32 專用的設定結構
    const STM32_EPD_Config *cfg = (const STM32_EPD_Config *)ctx;
    
    // 2. 使用結構中的 hspi (可能是 hspi1 或 hspi2)
    HAL_SPI_Transmit(cfg->hspi, &data, 1, 100);
}

// 實作 GPIO 寫入
static void stm32_gpio_write(const void *ctx, int pin_index, bool state) {
    const STM32_EPD_Config *cfg = (const STM32_EPD_Config *)ctx;
    GPIO_PinState pin_state = state ? GPIO_PIN_SET : GPIO_PIN_RESET;

    // 根據 pin_index 決定操作哪個 Port/Pin
    switch (pin_index) {
        case EPD_PIN_CS:
            HAL_GPIO_WritePin(cfg->cs_port, cfg->cs_pin, pin_state);
            break;
        case EPD_PIN_DC:
            HAL_GPIO_WritePin(cfg->dc_port, cfg->dc_pin, pin_state);
            break;
        case EPD_PIN_RESET:
            HAL_GPIO_WritePin(cfg->rst_port, cfg->rst_pin, pin_state);
            break;
    }
}

static bool stm32_gpio_read(const void *ctx, int pin_index) {
    const STM32_EPD_Config *cfg = (const STM32_EPD_Config *)ctx;
    GPIO_PinState pin_state;

    // 根據 pin_index 決定讀取哪個 Port/Pin
    switch (pin_index) {
        case EPD_PIN_BUSY:
            pin_state = HAL_GPIO_ReadPin(cfg->busy_port, cfg->busy_pin);
            return (pin_state == GPIO_PIN_SET);
        default:
            return false; // 不支援其他腳位讀取
    }
}

// 實作 Delay (不需要 ctx 但為了介面統一)
static void stm32_delay(const void *ctx, uint32_t ms) {
    (void)ctx; // 防止編譯警告
    HAL_Delay(ms);
}

// --- 建構子函式 ---
EPD_HAL EPD_HAL_InitSTM32(STM32_EPD_Config *config) {
    EPD_HAL hal;
    
    // 將使用者傳進來的 config 設為 user_data
    hal.user_data = (void*)config;
    
    // 綁定函式指標
    hal.spi_write_byte = stm32_spi_write_byte;
    hal.gpio_write = stm32_gpio_write;
    hal.gpio_read = stm32_gpio_read;
    hal.delay_ms = stm32_delay;
    hal.init = NULL;
    hal.spi_write_buffer = NULL;
    // ... 其他函式綁定
    
    return hal;
}
#endif // STM32_HAL_USAGE || USE_HAL_DRIVER