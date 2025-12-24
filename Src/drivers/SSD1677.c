// Src/drivers/SSD1677.c

#include "SSD1677.h"
#include "hal/epd_hal_interface.h"
#include "epd_driver_interface.h"

static void SSD1677_Reset(const EPD_HAL *hal);
static void SSD1677_WaitUntilIdle(const EPD_HAL *hal, uint32_t timeout_ms);
static void SSD1677_WriteCommand(const EPD_HAL *hal, uint8_t command);
static void SSD1677_WriteData(const EPD_HAL *hal, uint8_t data);
static void SSD1677_swReset(const EPD_HAL *hal);
static void SSD1677_Init(const EPD_HAL *hal);
static void SSD1677_setWidthHeight(const EPD_HAL *hal, uint16_t width, uint16_t height);
static void SSD1677_setCursor(const EPD_HAL *hal, uint16_t x, uint16_t y);
static void SSD1677_writeRamBegin(const EPD_HAL *hal, uint8_t color_layer);
static void SSD1677_writeRamEnd(const EPD_HAL *hal);
static void SSD1677_writeRam(const EPD_HAL *hal, const uint8_t* data, uint32_t length);
static void SSD1677_Update(const EPD_HAL *hal);

static void SSD1677_Reset(const EPD_HAL *hal) {
    // Hardware reset implementation
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, false);
    hal->delay_ms(hal->user_data, 200);
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, true);
    hal->delay_ms(hal->user_data, 200);
}

static void SSD1677_WriteCommand(const EPD_HAL *hal, uint8_t command) {
    hal->gpio_write(hal->user_data, EPD_PIN_DC, false);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, false);
    hal->spi_write_byte(hal->user_data, command);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
}

static void SSD1677_WriteData(const EPD_HAL *hal, uint8_t data) {
    hal->gpio_write(hal->user_data, EPD_PIN_DC, true);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, false);
    hal->spi_write_byte(hal->user_data, data);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
}

static void SSD1677_WaitUntilIdle(const EPD_HAL *hal, uint32_t timeout_ms) {
    uint32_t elapsed = 0;
    const uint32_t poll_interval = 1;

    while (elapsed < timeout_ms) {
        if (!hal->gpio_read(hal->user_data, EPD_PIN_BUSY)) {
            return;
        }
        hal->delay_ms(hal->user_data, poll_interval);
        elapsed += poll_interval;
    }
}

static void SSD1677_swReset(const EPD_HAL *hal){
    SSD1677_WriteCommand(hal, SSD1677_SW_RESET);
}

static void SSD1677_setwidthHeight(const EPD_HAL *hal, uint16_t width, uint16_t height){
    // Set RAM X and Y address start/end positions
    width--;
    height--;
    // width = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
    
    SSD1677_WriteCommand(hal, SSD1677_SET_RAM_Y_ADDRESS_START_END_POSITION);
    SSD1677_WriteData(hal, 0x00);
    SSD1677_WriteData(hal, 0x00);
    SSD1677_WriteData(hal, height & 0xFF);
    SSD1677_WriteData(hal, (height >> 8) & 0x03);
    SSD1677_WriteCommand(hal, SSD1677_SET_RAM_X_ADDRESS_START_END_POSITION);
    SSD1677_WriteData(hal, 0x00);
    SSD1677_WriteData(hal, 0x00);
    SSD1677_WriteData(hal, width & 0xFF);
    SSD1677_WriteData(hal, (width >> 8) & 0x03);
}

static void SSD1677_setCursor(const EPD_HAL *hal, uint16_t x, uint16_t y){
    SSD1677_WriteCommand(hal, SSD1677_SET_RAM_X_ADDRESS_COUNTER);
    SSD1677_WriteData(hal, x & 0xFF);
    SSD1677_WriteData(hal, (x >> 8) & 0x03);
    
    SSD1677_WriteCommand(hal, SSD1677_SET_RAM_Y_ADDRESS_COUNTER);
    SSD1677_WriteData(hal, y & 0xFF);
    SSD1677_WriteData(hal, (y >> 8) & 0x03);
}

static void SSD1677_Init(const EPD_HAL *hal){
    SSD1677_WriteCommand(hal, SSD1677_TEMP_SENSOR_CONTROL);
    SSD1677_WriteData(hal, SSD1677_TEMP_SENSOR_INTERNAL);
    SSD1677_WriteCommand(hal, SSD1677_DATA_ENTRY_MODE_SETTING);
    SSD1677_WriteData(hal, 0x03);
}

static void SSD1677_writeRamBegin(const EPD_HAL *hal, uint8_t color_layer){
    SSD1677_WriteCommand(hal, SSD1677_WRITE_RAM1);
}

static void SSD1677_writeRamEnd(const EPD_HAL *hal){
    // No specific end command for SSD1677
}

static void SSD1677_writeRam(const EPD_HAL *hal, const uint8_t* data, uint32_t length){
    for(uint32_t i = 0; i < length; i++){
        SSD1677_WriteData(hal, data[i]);
    }   
}

static void SSD1677_Update(const EPD_HAL *hal){
    SSD1677_WriteCommand(hal, SSD1677_DISPLAY_UPDATE_CONTROL_2);
    SSD1677_WriteData(hal, 0xF4);
    SSD1677_WriteCommand(hal, SSD1677_MASTER_ACTIVATION);   
    SSD1677_WaitUntilIdle(hal, 10000);
}

const EPD_Driver_Interface SSD1677_Driver = {
    .name = "SSD1677 Driver",
    .reset = SSD1677_Reset,
    .swReset = SSD1677_swReset,
    .init = SSD1677_Init,
    .set_window = SSD1677_setwidthHeight,
    .set_cursor = SSD1677_setCursor,
    .write_ram_begin = SSD1677_writeRamBegin,
    .write_ram_end = SSD1677_writeRamEnd,
    .write_ram = SSD1677_writeRam,
    .update = SSD1677_Update,
    .wait_busy = SSD1677_WaitUntilIdle,
    
};