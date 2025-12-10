// src/drivers/JD79661.c

#include "JD79661.h"
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

static void JD79661_WaitUntilIdle(const EPD_HAL *hal) {
    // Implementation of waiting for idle for JD79661
    while (hal->gpio_read(hal->user_data, EPD_PIN_BUSY)) {
        hal->delay_ms(hal->user_data, 1);
    }
}

static void JD79661_swReset(const EPD_HAL *hal){
    JD79661_WriteCommand(hal, 0x00); // Software reset command
    JD79661_WriteData(hal, 0x00);
    JD79661_WriteData(hal, 0x00);
    JD79661_WaitUntilIdle(hal);
}

static void JD79661_Init(const EPD_HAL *hal) {
    JD79661_Reset(hal);
    JD79661_WaitUntilIdle(hal);
    JD79661_swReset(hal);
    // Additional initialization commands can be added here
    JD79661_PowerSetting(hal);
    JD79661_BoosterSoftStart(hal);
    JD79661_PLLControl(hal);
    JD79661_TemperatureSensorCalibration(hal);
    JD79661_VCOMAndDataIntervalSetting(hal);
    JD79661_GateSourceStartSetting(hal);
    JD79661_PowerSaving(hal);


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
    JD79661_WriteCommand(hal, JD79661_RESOLUTION_SETTING);
    JD79661_WriteData(hal, width & 0xFF);
    JD79661_WriteData(hal, (width >> 8) & 0xFF);
    JD79661_WriteData(hal, height & 0xFF);
    JD79661_WriteData(hal, (height >> 8) & 0xFF);
}

static void JD79661_GateSourceStartSetting(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_GATE_SOURCE_START_SETTING);
    JD79661_WriteData(hal, 0x00); // Example gate source setting
    JD79661_WriteData(hal, 0x00); // Example gate source setting
    JD79661_WriteData(hal, 0x00); // Example gate source setting
    JD79661_WriteData(hal, 0x00); // Example gate source setting
}

static void JD79661_PowerSaving(const EPD_HAL *hal) {
    JD79661_WriteCommand(hal, JD79661_POWER_SAVING);
    JD79661_WriteData(hal, 0x22); // Example power saving setting
}





const EPD_Driver_Interface JD79661_Driver = {
    .name = "JD79661 Driver",
    .reset = JD79661_Reset,
    .swReset = JD79661_swReset,
    .set_window = JD79661_setWidthHeight,
    .init = JD79661_Init,
    // Additional driver function implementations can be added here
};