// src/drivers/JD79661.c

#include "drivers/JD79661.h"
#include "epd_api.h"
// Implement JD79661 driver functions here

// define JD79661 functions
static void JD79661_PowerSetting(const EPD_HAL *hal);
static void JD79661_BoosterSoftStart(const EPD_HAL *hal);
static void JD79661_PLLControl(const EPD_HAL *hal);
static void JD79661_TemperatureSensorCalibration(const EPD_HAL *hal);
static void JD79661_VCOMAndDataIntervalSetting(const EPD_HAL *hal);
static void JD79661_setWidthHeight(const EPD_HAL *hal, uint16_t width, uint16_t height);
static void JD79661_GateSourceStartSetting(const EPD_HAL *hal);
static void JD79661_PowerSaving(const EPD_HAL *hal);


// HW RESET
static void JD79661_Reset(const EPD_HAL *hal) {
    // Implementation of hardware reset for JD79661
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, true);
    hal->delay_ms(hal->user_data, 200); // Delay 200ms
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, false);
    hal->delay_ms(hal->user_data, 200); // Delay 200ms
    hal->gpio_write(hal->user_data, EPD_PIN_RESET, true);
    hal->delay_ms(hal->user_data, 200); // Delay 200ms
}

static void JD79661_WriteCommand(const EPD_HAL *hal, uint8_t command) {
    // Implementation of command write for JD79661
    hal->gpio_write(hal->user_data, EPD_PIN_DC, false);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, false);
    hal->spi_write_byte(hal->user_data, command);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
}

static void JD79661_WriteData(const EPD_HAL *hal, uint8_t data) {
    // Implementation of data write for JD79661
    hal->gpio_write(hal->user_data, EPD_PIN_DC, true);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, false);
    hal->spi_write_byte(hal->user_data, data);
    hal->gpio_write(hal->user_data, EPD_PIN_CS, true);
}

static uint8_t JD79661_WaitUntilIdle(const EPD_HAL *hal, uint32_t timeout_ms) {
    // Implementation of waiting for idle for JD79661
    uint32_t elapsed = 0;
    while (!(hal->gpio_read(hal->user_data, EPD_PIN_BUSY))) {
        if (elapsed >= timeout_ms) {
            break;
        }
        hal->delay_ms(hal->user_data, 1);
        elapsed++;
    }
    return (elapsed < timeout_ms) ? EPD_OK : EPD_ERROR_TIMEOUT; // 0: OK, 1: Timeout
}

static void JD79661_swReset(const EPD_HAL *hal){
    JD79661_WriteCommand(hal, 0x4D); // Software reset command
    JD79661_WriteData(hal, 0x78);
    JD79661_WriteCommand(hal, 0x00); // Software reset command
    JD79661_WriteData(hal, 0x0F);
    JD79661_WriteData(hal, 0x09);
}

static void JD79661_Init(const EPD_HAL *hal) {
    // Additional initialization commands can be added here
    JD79661_PowerSetting(hal);
    
    JD79661_WriteCommand(hal, 0x03);
    JD79661_WriteData(hal, 0x10);
    JD79661_WriteData(hal, 0x54);
    JD79661_WriteData(hal, 0x44);
    
    JD79661_BoosterSoftStart(hal);
    JD79661_PLLControl(hal);
    JD79661_TemperatureSensorCalibration(hal);
    JD79661_VCOMAndDataIntervalSetting(hal);

    JD79661_WriteCommand(hal, 0x60);
    JD79661_WriteData(hal, 0x02);
    JD79661_WriteData(hal, 0x02);
    
    JD79661_WriteCommand(hal, 0x61);
    JD79661_WriteData(hal, 0x00);
    JD79661_WriteData(hal, 0x80);
    JD79661_WriteData(hal, 0x00);
    JD79661_WriteData(hal, 0xFA);
    

    JD79661_GateSourceStartSetting(hal);

    JD79661_WriteCommand(hal, 0xE7);
    JD79661_WriteData(hal, 0x1C);

    JD79661_PowerSaving(hal);
    
    JD79661_WriteCommand(hal, 0xE0);
    JD79661_WriteData(hal, 0x00);

    JD79661_WriteCommand(hal, 0xB4);
    JD79661_WriteData(hal, 0xD0);

    JD79661_WriteCommand(hal, 0xB5);
    JD79661_WriteData(hal, 0x03);

    JD79661_WriteCommand(hal, 0xE9);
    JD79661_WriteData(hal, 0x01);
    


}

static void JD79661_PowerSetting(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_POWER_SETTING);
    JD79661_WriteData(hal, 0x07); 
    JD79661_WriteData(hal, 0x00); 
    JD79661_WriteData(hal, 0x22); 
    JD79661_WriteData(hal, 0x78); 
    JD79661_WriteData(hal, 0x0A); 
    JD79661_WriteData(hal, 0x22); 
}

static void JD79661_BoosterSoftStart(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_BOOSTER_SOFT_START);
    JD79661_WriteData(hal, 0x0F);
    JD79661_WriteData(hal, 0x0A);
    JD79661_WriteData(hal, 0x2F);
    JD79661_WriteData(hal, 0x25);
    JD79661_WriteData(hal, 0x22);
    JD79661_WriteData(hal, 0x2E);
    JD79661_WriteData(hal, 0x21); 
}

static void JD79661_PLLControl(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_PLL_CONTROL);
    JD79661_WriteData(hal, 0x02); // Example PLL setting
}

static void JD79661_TemperatureSensorCalibration(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_TEMPERATURE_CALIBRATION);
    JD79661_WriteData(hal, 0x00); // Example calibration data
}

static void JD79661_VCOMAndDataIntervalSetting(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_VCOM_AND_DATA_INTERVAL_SETTING);
    JD79661_WriteData(hal, 0x37); // Example VCOM and data interval setting
}

static void JD79661_setWidthHeight(const EPD_HAL *hal, uint16_t width, uint16_t height){
    // JD79661_WriteCommand(hal, JD79661_RESOLUTION_SETTING);
    // JD79661_WriteData(hal, (width >> 8) & 0xFF);
    // JD79661_WriteData(hal, (((width + 7) >> 3) << 3) & 0xFF);
    // JD79661_WriteData(hal, (height >> 8) & 0xFF);
    // JD79661_WriteData(hal, height & 0xFF);
}

static void JD79661_GateSourceStartSetting(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_GATE_SOURCE_START_SETTING);
    JD79661_WriteData(hal, 0x00);
    JD79661_WriteData(hal, 0x00);
    JD79661_WriteData(hal, 0x00);
    JD79661_WriteData(hal, 0x00);
}

static void JD79661_PowerSaving(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_POWER_SAVING);
    JD79661_WriteData(hal, 0x22); // Example power saving setting
}

static void JD79661_write_ram(const EPD_HAL *hal, const uint8_t* data, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        JD79661_WriteData(hal, data[i]);
    }
}

static void JD79661_write_ram_start(const EPD_HAL *hal, uint8_t color_layer) {
    JD79661_WriteCommand(hal, JD79661_DATA_START_TRANSMISSION_1);
}

static void JD79661_write_ram_end(const EPD_HAL *hal) {
    // JD79661_WriteCommand(hal, JD79661_DATA_STOP);
}

static void JD79661_update(const EPD_HAL *hal) {
    // JD79661_WriteCommand(hal, JD79661_AUTO_SEQUENCE);
    // JD79661_WriteData(hal, 0xA5); 
    JD79661_WriteCommand(hal, JD79661_POWER_ON);
    JD79661_WaitUntilIdle(hal, 5000);
    JD79661_WriteCommand(hal, JD79661_DISPLAY_REFRESH);
    JD79661_WriteData(hal, 0x00);
}




const EPD_Driver_Interface JD79661_Driver = {
    .name = "JD79661 Driver",
    .reset = JD79661_Reset,
    .swReset = JD79661_swReset,
    .set_window = JD79661_setWidthHeight,
    .init = JD79661_Init,
    .write_ram = JD79661_write_ram,
    .write_ram_begin = JD79661_write_ram_start,
    .write_ram_end = JD79661_write_ram_end,
    .update = JD79661_update,
    .wait_busy = JD79661_WaitUntilIdle,
    // Additional driver function implementations can be added here
};