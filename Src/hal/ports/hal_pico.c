// src/hal/ports/hal_pico.c
#if defined(PICO_ON_DEVICE)
#include "hal_pico.h"

static void pico_spi_write_byte(const void *ctx, uint8_t data) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    spi_write_blocking(cfg->spi, &data, 1);
}

static void pico_spi_write_buffer(const void *ctx, const uint8_t* data, uint32_t len) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    spi_write_blocking(cfg->spi, data, len);
}

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

static bool pico_gpio_read(const void *ctx, int pin_index) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    if (pin_index == EPD_PIN_BUSY) {
        return gpio_get(cfg->pin_busy);
    }
    return false;
}

static void pico_delay(const void *ctx, uint32_t ms) {
    (void)ctx;
    sleep_ms(ms);
}

static void pico_internal_init_gpio(const void *ctx) {
    const Pico_EPD_Config *cfg = (const Pico_EPD_Config *)ctx;
    
    gpio_init(cfg->pin_cs);  gpio_set_dir(cfg->pin_cs, GPIO_OUT);
    gpio_init(cfg->pin_dc);  gpio_set_dir(cfg->pin_dc, GPIO_OUT);
    gpio_init(cfg->pin_rst); gpio_set_dir(cfg->pin_rst, GPIO_OUT);
    
    gpio_init(cfg->pin_busy); gpio_set_dir(cfg->pin_busy, GPIO_IN);
    
    gpio_put(cfg->pin_cs, 1);
}

EPD_HAL EPD_HAL_InitPico(Pico_EPD_Config *config) {
    EPD_HAL hal;
    hal.user_data = (void*)config;

    hal.spi_write_byte = pico_spi_write_byte;
    hal.spi_write_buffer = pico_spi_write_buffer;
    hal.gpio_write = pico_gpio_write;
    hal.gpio_read = pico_gpio_read;
    hal.delay_ms = pico_delay;
    
    hal.init = pico_internal_init_gpio;

    return hal;
}

#endif