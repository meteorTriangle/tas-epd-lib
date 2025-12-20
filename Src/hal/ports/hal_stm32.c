// src/hal/ports/hal_stm32.c

#include "hal_stm32.h"
#ifdef STM32

static void stm32_spi_write_byte(const void *ctx, uint8_t data) {
    const STM32_EPD_Config *cfg = (const STM32_EPD_Config *)ctx;
    
    HAL_SPI_Transmit(cfg->hspi, &data, 1, 100);
}

static void stm32_gpio_write(const void *ctx, int pin_index, bool state) {
    const STM32_EPD_Config *cfg = (const STM32_EPD_Config *)ctx;
    GPIO_PinState pin_state = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
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

    switch (pin_index) {
        case EPD_PIN_BUSY:
            pin_state = HAL_GPIO_ReadPin(cfg->busy_port, cfg->busy_pin);
            return (pin_state == GPIO_PIN_SET);
        default:
            return false;
    }
}

static void stm32_delay(const void *ctx, uint32_t ms) {
    (void)ctx;
    HAL_Delay(ms);
}

EPD_HAL EPD_HAL_InitSTM32(STM32_EPD_Config *config) {
    EPD_HAL hal;
    
    hal.user_data = (void*)config;
    
    hal.spi_write_byte = stm32_spi_write_byte;
    hal.gpio_write = stm32_gpio_write;
    hal.gpio_read = stm32_gpio_read;
    hal.delay_ms = stm32_delay;
    hal.init = NULL;
    hal.spi_write_buffer = NULL;
    
    return hal;
}
#endif // STM32_HAL_USAGE || USE_HAL_DRIVER