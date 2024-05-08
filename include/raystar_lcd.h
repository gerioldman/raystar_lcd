/**
 * @file LCD_Driver.h
 * @brief TODO
 * @date 2022-11-27-23:43:26
*/
#ifndef LCD_Driver_H
#define LCD_Driver_H

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>


/* Type definitions ----------------------------------------------------------*/

typedef enum{
    PIXEL_SET,
    PIXEL_RESET
} Pixel_State;

/* Defines -------------------------------------------------------------------*/


#define LCD_PIXEL_SET 1
#define LCD_PIXEL_RESET 0
#define LCD_HEIGHT 64
#define LCD_WIDTH 128
#define LCD_COMMAND_DISPLAY_ON 0x3F
#define LCD_COMMAND_DISPLAY_OFF 0x3E
#define LCD_PAGE_NUMBER 8
#define LCD_SETYADDRESS 0x40
#define LCD_SETPAGE 0xB8
#define LCD_DISPLAY_START_LINE 0xC0

/* Global variables ----------------------------------------------------------*/

extern const unsigned char font8x8_basic[128][8];

/* Function declarations -----------------------------------------------------*/

/**
 * @brief Initialize LCD
 * 
 */
void LCD_Init();

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
void LCD_Invalidate();

/**
 * @brief Writes a pixel in the buffer
 * 
 * @param pixel The value of the pixel, write 1 to set, 0 to reset
 * @param x position in the x direction
 * @param y position in the y direction
 */
void LCD_Write_BufferPixel(Pixel_State pixel, int16_t x,int16_t y);



#endif /* LCD_Driver_H */