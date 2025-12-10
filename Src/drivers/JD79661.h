// src/drivers/JD79661.h
#ifndef JD79661_H
#define JD79661_H

#include "epd_types.h"

#define JD79661_PANEL_SETTING                0x00
#define JD79661_POWER_SETTING                0x01
#define JD79661_POWER_OFF                    0x02
#define JD79661_POWER_ON                     0x04
#define JD79661_BOOSTER_SOFT_START           0x06
#define JD79661_DEEP_SLEEP                   0x07
#define JD79661_DATA_START_TRANSMISSION_1    0x10
#define JD79661_DATA_STOP                    0x11
#define JD79661_DISPLAY_REFRESH              0x12
#define JD79661_AUTO_SEQUENCE                0x17
#define JD79661_PLL_CONTROL                  0x30
#define JD79661_TEMPERATURE_CALIBRATION      0x41
#define JD79661_TEMPERATURE_SENSOR_WRITE     0x42
#define JD79661_TEMPERATURE_SENSOR_READ      0x43
#define JD79661_VCOM_AND_DATA_INTERVAL_SETTING 0x50
#define JD79661_LOW_POWER_DETECTION          0x51
#define JD79661_RESOLUTION_SETTING           0x61
#define JD79661_GATE_SOURCE_START_SETTING    0x65
#define JD79661_GET_CHIP_REVISION            0x70
#define JD79661_AUTO_MEASURE_VCOM            0x80
#define JD79661_VCOM_VALUE                   0x81
#define JD79661_VCM_DC_SETTING_REGISTER      0x82
#define JD79661_PARTIAL_WINDOW               0x83
#define JD79661_PROGRAM_MODE                 0x90
#define JD79661_ACTIVE_PROGRAM               0x91
#define JD79661_READ_MTP_DATA                0x92
#define JD79661_READ_MTP_RESERVED            0x9F
#define JD79661_POWER_SAVING                 0xE3
#define JD79661_LVDS_SETTING                 0xE4



#endif // JD79661_H