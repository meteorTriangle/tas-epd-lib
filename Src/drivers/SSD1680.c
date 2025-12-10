// src/drivers/SSD1680.c
#include "SSD1680.h"
#include "hal/epd_hal_interface.h"
#include "epd_driver_interface.h"
#include <stdint.h>

static void SSD1680_Reset(const EPD_HAL *hal) {
    // 將 RESET 腳拉低
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, true);
    hal->delay_ms(hal->user_data, 200); // 延遲 200ms
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, false);
    hal->delay_ms(hal->user_data, 200); // 延遲 200ms

    // 將 RESET 腳拉高
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, true);
    hal->delay_ms(hal->user_data, 200); // 延遲 200ms
}

static void SSD1680_WriteCommand(const EPD_HAL *hal, uint8_t command) {
    // 將 DC 腳拉低表示傳送命令
    hal->gpio_write(hal->user_data, EPD_PIN_DC, false);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, false);
    hal->spi_write_byte(hal->user_data, command);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
}
static void SSD1680_WriteData(const EPD_HAL *hal, uint8_t data) {
    // 將 DC 腳拉高表示傳送資料
    hal->gpio_write(hal->user_data, EPD_PIN_DC, true);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, false);
    hal->spi_write_byte(hal->user_data, data);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
}
static void SSD1680_WaitUntilIdle(const EPD_HAL *hal, uint32_t timeout_ms) {
    uint32_t elapsed = 0;
    const uint32_t poll_interval = 1; // 每次輪詢間隔 1ms

    while (elapsed < timeout_ms) {
        if (!hal->gpio_read(hal->user_data, EPD_PIN_BUSY)) {
            return; // 裝置已閒置
        }
        hal->delay_ms(hal->user_data, poll_interval);
        elapsed += poll_interval;
    }
}

static void SSD1680_swReset(const EPD_HAL *hal){
    SSD1680_WriteCommand(hal, SSD1680_SW_RESET);
    SSD1680_WaitUntilIdle(hal, 5000);
}

static void SSD1680_setWidthHeight(const EPD_HAL *hal, uint16_t width, uint16_t height){
    uint16_t width_bytes = (width + 7) / 8;
    SSD1680_WriteCommand(hal, SSD1680_SET_RAM_X_ADDRESS_START_END);
    SSD1680_WriteData(hal, 0x00);
    SSD1680_WriteData(hal, ((width_bytes+7)/8) - 1);

    SSD1680_WriteCommand(hal, SSD1680_SET_RAM_Y_ADDRESS_START_END);
    SSD1680_WriteData(hal, 0x00);
    SSD1680_WriteData(hal, 0x00);
    SSD1680_WriteData(hal, (height - 1) & 0xFF);
    SSD1680_WriteData(hal, ((height - 1) >> 8) & 0xFF);
}

static void SSD1680_setXYAddressCounter(const EPD_HAL *hal, uint16_t x, uint16_t y){
    uint16_t x_bytes = x / 8;
    SSD1680_WriteCommand(hal, SSD1680_SET_RAM_X_ADDRESS_COUNTER);
    SSD1680_WriteData(hal, x_bytes);

    SSD1680_WriteCommand(hal, SSD1680_SET_RAM_Y_ADDRESS_COUNTER);
    SSD1680_WriteData(hal, y & 0xFF);
    SSD1680_WriteData(hal, (y >> 8) & 0xFF);
}

static void SSD1680_WriteRamBegin(const EPD_HAL *hal, uint8_t color_mode){
    SSD1680_WriteCommand(hal, color_mode);
}

static void SSD1680_setDataEntryMode(EPD_HAL *hal, uint8_t mode){
    SSD1680_WriteCommand(hal, SSD1680_DATA_ENTRY_MODE_SETTING); // DATA ENTRY MODE 設定命令
    SSD1680_WriteData(hal, mode);
}

static void SSD1680_setLUT(EPD_HAL *hal, void* lutv){
    lut_t* lut = (lut_t*)lutv;
    SSD1680_WriteCommand(hal, SSD1680_WRITE_LUT_REGISTER);
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 12; i++){
            SSD1680_WriteData(hal, (lut->wave[i].LUT[j][0] << 6) | (lut->wave[i].LUT[j][1] << 4) | (lut->wave[i].LUT[j][2] << 2) | (lut->wave[i].LUT[j][3]));
        }
    }
    for(int i = 0; i < 12; i++){
        SSD1680_WriteData(hal, lut->wave[i].continus_time[0]);
        SSD1680_WriteData(hal, lut->wave[i].continus_time[1]);
        SSD1680_WriteData(hal, lut->wave[i].repeat_time_AB);
        SSD1680_WriteData(hal, lut->wave[i].continus_time[2]);
        SSD1680_WriteData(hal, lut->wave[i].continus_time[3]);
        SSD1680_WriteData(hal, lut->wave[i].repeat_time_CD);
        SSD1680_WriteData(hal, lut->wave[i].repeat_time_group);
    }
    for(int i = 0; i < 6; i++){
        SSD1680_WriteData(hal, (lut->wave[i*2].FR << 4) | (lut->wave[i*2+1].FR));
    }
    for(int i = 0; i < 3; i++){
        SSD1680_WriteData(hal, 
            (lut->wave[i*4].xon_AB<<7) |
            (lut->wave[i*4].xon_CD<<6) |
            (lut->wave[i*4+1].xon_AB<<5) |
            (lut->wave[i*4+1].xon_CD<<4) |
            (lut->wave[i*4+2].xon_AB<<3) |
            (lut->wave[i*4+2].xon_CD<<2) |
            (lut->wave[i*4+3].xon_AB<<1) |
            (lut->wave[i*4+3].xon_CD)
        );
    }
    SSD1680_WriteCommand(hal, SSD1680_GATE_DRIVING_VOLTAGE_CONTROL);
    SSD1680_WriteData(hal, lut->VGH);
    SSD1680_WriteCommand(hal, SSD1680_SOURCE_DRIVING_VOLTAGE_CONTROL);
    SSD1680_WriteData(hal, lut->VSH1);
    SSD1680_WriteData(hal, lut->VSH2);
    SSD1680_WriteData(hal, lut->VSL);
    SSD1680_WriteCommand(hal, SSD1680_WRITE_REGISTER_VCOM_CONTROL);
    SSD1680_WriteData(hal, lut->VCOM);
}

static void SSD1680_Update(const EPD_HAL *hal){
    SSD1680_WriteCommand(hal, SSD1680_DISPLAY_UPDATE_CONTROL_2);
    SSD1680_WriteData(hal, 0xF4);
    SSD1680_WriteCommand(hal, SSD1680_MASTER_ACTIVATION);
    SSD1680_WaitUntilIdle(hal, 5000);
}

static void SSD1680_WRITE_RAM(const EPD_HAL* hal, const uint8_t* data, uint16_t length){
    // SSD1680_WriteCommand(hal, SSD1680_WRITE_RAM1);
    for(uint32_t i = 0; i < length; i++){
        SSD1680_WriteData(hal, data[i]);
    }
}

const EPD_Driver_Interface SSD1680_Driver = {
    .name = "SSD1680 Driver",
    .reset = SSD1680_Reset,
    .swReset = SSD1680_swReset,
    .set_window = SSD1680_setWidthHeight,
    .set_cursor = SSD1680_setXYAddressCounter,
    .write_ram_begin = SSD1680_WriteRamBegin,
    .write_ram = SSD1680_WRITE_RAM,              // 由 Core 層處理
    .update = SSD1680_Update,          // 由 Core 層處理
    .wait_busy = SSD1680_WaitUntilIdle,
    .sleep = NULL,           // 由 Core 層處理
    // .load_lut = SSD1680_setLUT,
};