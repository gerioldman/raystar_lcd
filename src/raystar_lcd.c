/**
 * @file raystar_lcd.c
 * @author gerioldman (k.gergo49@gmail.com)
 * @brief Implementation of the driver
 */

/* Private includes ----------------------------------------------------------*/

#include "raystar_lcd.h"
#include "raystar_lcd_interface.h"

/* Private macros ------------------------------------------------------------*/

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

/* Private variables ---------------------------------------------------------*/

static uint8_t buffer_left[8][64];
static uint8_t buffer_right[8][64];

/* Local function declarations -----------------------------------------------*/

static void LCD_Write(uint8_t value, LCD_HWI_CS_Lines_State CSState, LCD_HWI_Instruction_Data_State DIState);
static void LCD_Data_Latch();

/* Local function definitions ------------------------------------------------*/

static void LCD_Write(uint8_t value, LCD_HWI_CS_Lines_State CSState, LCD_HWI_Instruction_Data_State DIState)
{
	LCD_HWI_SetDILine(DIState);
	LCD_HWI_SetCSLines(CSState);
	LCD_HWI_SetDataLines(value);
	LCD_Data_Latch();
	LCD_HWI_SetCSLines(LCD_HWI_CS_OFF);
}
static void LCD_Data_Latch()
{
	LCD_HWI_Delay(1);
	LCD_HWI_SetLatch(LCD_HWI_Latch_OFF);
	LCD_HWI_Delay(1);
	LCD_HWI_SetLatch(LCD_HWI_Latch_ON);
	LCD_HWI_Delay(1);
}

/* Global function definitions -----------------------------------------------*/

void LCD_Init()
{
	LCD_HWI_SetEnable(LCD_HWI_Enable_OFF);
	LCD_HWI_SetLatch(LCD_HWI_Latch_ON);
	LCD_HWI_SetRWLine(LCD_HWI_RW_Write);
	LCD_HWI_SetReset(LCD_HWI_RST_OFF);
	LCD_HWI_SetCSLines(LCD_HWI_CS_OFF);

	LCD_HWI_SetEnable(LCD_HWI_Enable_ON);

	LCD_Write(LCD_COMMAND_DISPLAY_ON, LCD_HWI_CS12, LCD_HWI_DI_Instruction);

	LCD_Write(LCD_SETYADDRESS, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
	LCD_Write(LCD_SETPAGE, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
	LCD_Write(LCD_DISPLAY_START_LINE, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
}

void LCD_Fill_Display(uint8_t value)
{
	for (uint8_t p = 0; p < LCD_PAGE_NUMBER; p++)
	{
		LCD_Write(LCD_SETYADDRESS, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
		LCD_Write(LCD_SETPAGE | p, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
		for (uint8_t i = 0; i < 64; i++)
		{
			LCD_Write(value, LCD_HWI_CS12, LCD_HWI_DI_Data);
		}
	}
}
void LCD_Write_BufferPixel(Pixel_State pixel, int16_t x, int16_t y)
{
	// Left side
	if (x < 64 && x >= 0)
	{
		if (y < 64 && y >= 0)
		{

			if (pixel)
				buffer_left[y >> 3][x] |= (1 << (y % 8)); // Set bit
			else
				buffer_left[y >> 3][x] &= ~(1 << (y % 8)); // Clear bit
		}
	}
	// Right side
	else if (x < 128 && x >= 64)
	{
		if (y < 64 && y >= 0)
		{
			if (pixel)
				buffer_right[y >> 3][x - 64] |= (1 << (y % 8)); // Set bit
			else
				buffer_right[y >> 3][x - 64] &= ~(1 << (y % 8)); // Clear bit
		}
	}
}
void LCD_Invalidate()
{
	for (uint8_t p = 0; p < LCD_PAGE_NUMBER; p++)
	{
		LCD_Write(LCD_SETYADDRESS, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
		LCD_Write(LCD_SETPAGE | p, LCD_HWI_CS12, LCD_HWI_DI_Instruction);
		for (uint8_t i = 0; i < LCD_WIDTH / 2; i++)
		{
			LCD_Write(buffer_left[p][i], LCD_HWI_CS1, LCD_HWI_DI_Data);
		}
		for (uint8_t i = 0; i < LCD_WIDTH / 2; i++)
		{
			LCD_Write(buffer_right[p][i], LCD_HWI_CS2, LCD_HWI_DI_Data);
		}
	}
}

void LCD_Fill_Buffer(uint8_t value)
{
	for (int i = 0; i < 8; i++)
	{
		for (int var = 0; var < 64; ++var)
		{
			buffer_left[i][var] = value;
			buffer_right[i][var] = value;
		}
	}
}
