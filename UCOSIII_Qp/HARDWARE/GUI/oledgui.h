#ifndef __OLEDGUI_H
#define __OLEDGUI_H 
#include <string.h>
#include "delay.h"
#include "spi_oled.h"


#define Max_Column	128
#define Max_Row			64
#define	Brightness	0xFF 
#define X_WIDTH 		128
#define Y_WIDTH 		64	 

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 back_mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 back_mode);
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 size);
void Show_ClkNum(uint8_t x,uint8_t y,char n,char font);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);



void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(int x1,int y1,int x2,int y2,int color);
void OLED_DrawRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(int x, int y, int r, int color);
void OLED_Refresh_GRAM(uint8_t op);
void OLED_Clean_GRAM(uint8_t t);
void show_loading(u8 count,u8 start_lin,u8 start_col);// 1 44;
void SHOW_CG(void);
#endif

