// inc/epd_api.h

/**
 * @file epd_api.h
 * @brief EPD API functions for initializing and controlling e-paper displays.
 * This file defines the high-level API for interacting with e-paper displays,
 * including initialization, image writing, and display updating.
 * @author Triangle Alien
 * @date 2025-12-20
 */

#ifndef EPD_API_H
#define EPD_API_H
#include "epd_types.h"
#include <stddef.h>

/**
 * @name EPD_Status_Codes
 * these codes are returned by EPD API functions to indicate success or specific error conditions.
 * @{
 */

#define EPD_OK                      0x00  /**< @brief operation successful */
#define EPD_ERROR                   0x01  /**< @brief unknown error */
#define EPD_ERROR_NULL_PTR          0x02  /**<  @brief Handle or Driver pointer is NULL */
#define EPD_ERROR_INVALID_PARAM     0x03  /**<  @brief Invalid parameter (e.g., width or height is 0) */
#define EPD_ERROR_BUSY              0x04  /**<  @brief Device is busy (e.g., Busy Pin not released) */
#define EPD_ERROR_TIMEOUT           0x05  /**<  @brief Timeout occurred */
#define EPD_ERROR_NOT_SUPPORTED     0x06  /**<  @brief Feature not supported by the driver (e.g., callback is NULL) */
#define EPD_ERROR_HAL               0x07  /**<  @brief HAL layer error (e.g., SPI transmission failure) */
#define EPD_ERROR_DRIVER            0x08  /**<  @brief Driver layer error (e.g., driver initialization failure) */
/** @} */


/**
 * @brief Initialize the EPD handle with the given HAL and profile.
 * @param handle Pointer to the EPD handle to initialize.
 * @param hal Pointer to the hardware abstraction layer (HAL) configuration.
 * @param profile Pointer to the EPD profile configuration.
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_API_Init(EPD_Handle* handle, const EPD_HAL* hal, const EPD_Profile* profile);

/**
 * @brief Initialize the EPD display.
 * This function performs hardware and software resets, and prepares the display for use.
 * @param handle Pointer to the EPD handle.
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_Init(EPD_Handle* handle);

/**
 * @brief Set the cursor position on the EPD display.
 * @param handle Pointer to the EPD handle.
 * @param x X coordinate of the cursor position.
 * @param y Y coordinate of the cursor position.
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_setCursor(EPD_Handle* handle, uint16_t x, uint16_t y);

/**
 * @brief Write image data to the EPD display.
 * @param handle Pointer to the EPD handle.
 * @param image_data Pointer to the image data buffer.
 * @param data_length Length of the image data in bytes.
 * @param color_layer Color layer to write (e.g., 0 for black/white, 1 for red).
 * @return Status code indicating success or error. @link EPD_Status_Codes
 * @note This function handles the entire process of writing image data, including
 * beginning the write, sending the data, and ending the write.
 */
uint8_t EPD_WriteImage(EPD_Handle* handle, const uint8_t* image_data, uint32_t data_length, uint8_t color_layer);

/**
 * @brief Update the EPD display to reflect the written image data.
 * @param handle Pointer to the EPD handle.
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_Update(EPD_Handle* handle);

/**
 * @brief Start writing image data to the EPD display.
 * @param handle Pointer to the EPD handle.
 * @param color_layer Color layer to write (e.g., 0 for black/white, 1 for red).
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_StartWriteImage(EPD_Handle* handle, uint8_t color_layer);

/**
 * @brief End writing image data to the EPD display.
 * @param handle Pointer to the EPD handle.
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_EndWriteImage(EPD_Handle* handle);

/**
 * @brief Write image data to the EPD display in separate steps.
 * @param handle Pointer to the EPD handle.
 * @param image_data Pointer to the image data buffer.
 * @param data_length Length of the image data in bytes.
 * @param color_layer Color layer to write (e.g., 0 for black/white, 1 for red).
 * @return Status code indicating success or error. @link EPD_Status_Codes
 */
uint8_t EPD_WriteImageSeperately(EPD_Handle* handle, const uint8_t* image_data, uint32_t data_length, uint8_t color_layer);



#endif // EPD_API_H