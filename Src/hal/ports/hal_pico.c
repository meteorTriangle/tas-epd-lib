// src/hal/ports/hal_pico.c
#if defined(PICO_ON_DEVICE)
#include "hal_pico.h"

// --- 實作細節 ---

// 寫入單 byte
static void pico_spi_write_byte(const void *ctx, uint8_t data) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    // 使用阻塞式寫入 (Blocking Write)
    spi_write_blocking(cfg->spi, &data, 1);
}

// 寫入 Buffer (Pico 的 SPI FIFO 很有效率)
static void pico_spi_write_buffer(const void *ctx, const uint8_t* data, uint32_t len) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    spi_write_blocking(cfg->spi, data, len);
}

// GPIO 控制
static void pico_gpio_write(const void *ctx, int pin_index, bool state) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    uint8_t gpio_num = 0;

    switch (pin_index) {
        case EPD_PIN_CS:    gpio_num = cfg->pin_cs; break;
        case EPD_PIN_DC:    gpio_num = cfg->pin_dc; break;
        case EPD_PIN_RESET: gpio_num = cfg->pin_rst; break;
        default: return;
    }
    
    gpio_put(gpio_num, state);
}

// 讀取 Busy 腳
static bool pico_gpio_read(const void *ctx, int pin_index) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    if (pin_index == EPD_PIN_BUSY) {
        return gpio_get(cfg->pin_busy);
    }
    return false;
}

// 延遲
static void pico_delay(const void *ctx, uint32_t ms) {
    (void)ctx;
    sleep_ms(ms);
}

// 初始化 GPIO 方向 (這是一個 Optional 的 helper，幫使用者設定 GPIO 方向)
static void pico_internal_init_gpio(const void *ctx) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    
    // 初始化並設定為輸出
    gpio_init(cfg->pin_cs);  gpio_set_dir(cfg->pin_cs, GPIO_OUT);
    gpio_init(cfg->pin_dc);  gpio_set_dir(cfg->pin_dc, GPIO_OUT);
    gpio_init(cfg->pin_rst); gpio_set_dir(cfg->pin_rst, GPIO_OUT);
    
    // 初始化並設定為輸入
    gpio_init(cfg->pin_busy); gpio_set_dir(cfg->pin_busy, GPIO_IN);
    
    // 預設拉高 CS (Deselect)
    gpio_put(cfg->pin_cs, 1);
}

// --- 建構 HAL 物件 ---
EPD_HAL EPD_HAL_InitPico(Pico_EPD_Config *config) {
    EPD_HAL hal;
    hal.user_data = (void*)config;

    // 綁定函式
    hal.spi_write_byte = pico_spi_write_byte;
    hal.spi_write_buffer = pico_spi_write_buffer;
    hal.gpio_write = pico_gpio_write;
    hal.gpio_read = pico_gpio_read;
    hal.delay_ms = pico_delay;
    
    // 這裡我們把 GPIO 方向設定放在 init 裡
    hal.init = pico_internal_init_gpio;

    return hal;
}

#endif