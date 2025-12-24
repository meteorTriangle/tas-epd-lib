// Src/drivers/SSD1677.h
#ifndef SSD1677_H
#define SSD1677_H

#include "hal/epd_hal_interface.h"
#include "epd_types.h"

#define SSD1677_DRIVER_OUTPUT_CONTROL                    0x01
#define SSD1677_GATE_DRIVING_VOLTAGE_CONTROL             0x03
#define SSD1677_SOURCE_DRIVING_VOLTAGE_CONTROL           0x04
#define SSD1677_DEEP_SLEEP_MODE                          0x10
#define SSD1677_DATA_ENTRY_MODE_SETTING                  0x11
#define SSD1677_SW_RESET                                 0x12
#define SSD1677_TEMP_SENSOR_CONTROL                      0x18
    #define SSD1677_TEMP_SENSOR_EXTERNAL                 0x48
    #define SSD1677_TEMP_SENSOR_INTERNAL                 0x80
#define SSD1677_MASTER_ACTIVATION                        0x20
#define SSD1677_DISPLAY_UPDATE_CONTROL_2                 0x22
#define SSD1677_WRITE_RAM1                               0x24
#define SSD1677_WRITE_RAM2                               0x25
#define SSD1677_WRITE_LUT_REGISTER                       0x32
#define SSD1677_BORDER_WAVEFORM_CONTROL                  0x3C
#define SSD1677_SET_RAM_X_ADDRESS_START_END_POSITION     0x44
#define SSD1677_SET_RAM_Y_ADDRESS_START_END_POSITION     0x45
#define SSD1677_SET_RAM_X_ADDRESS_COUNTER                0x4E
#define SSD1677_SET_RAM_Y_ADDRESS_COUNTER                0x4F

extern const EPD_Driver_Interface SSD1677_Driver;

#endif // SSD1677_H