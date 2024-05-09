/**
 * @file raystar_lcd.h
 * @author gerioldman (k.gergo49@gmail.com)
 * @brief Raystar LCD driver header
 */

#ifndef RAYSTAR_LCD_H
#define RAYSTAR_LCD_H

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/* Type definitions ----------------------------------------------------------*/

typedef enum
{
    PIXEL_SET,
    PIXEL_RESET
} Pixel_State;

/* Defines -------------------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Function declarations -----------------------------------------------------*/

/**
 * @brief Initialize LCD
 *
 */
void LCD_Init(void);

/**
 * @brief Sends display off command, turns off enable pin and sets reset pin
 * 
 */
void LCD_DeInit(void);

/**
 * @brief Fill the display with the given pattern
 *
 * @param value Fills the buffer with the given pattern and writes it to the screen
 */
void LCD_Fill_Display(uint8_t value);

/**
 * @brief Fill the buffer with the given pattern
 *
 * @param value Fills the buffer with the given pattern
 */
void LCD_Fill_Buffer(uint8_t value);

/**
 * @brief Writes the content of the buffer to the LCD screen
 *
 */
void LCD_Invalidate(void);

/**
 * @brief Writes a pixel in the buffer
 *
 * @param pixel The value of the pixel, write 1 to set, 0 to reset
 * @param x position in the x direction
 * @param y position in the y direction
 */
void LCD_Write_BufferPixel(Pixel_State pixel, int16_t x, int16_t y);

#endif /* RAYSTAR_LCD_H */