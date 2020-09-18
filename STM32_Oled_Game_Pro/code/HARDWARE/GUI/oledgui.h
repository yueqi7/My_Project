#ifndef __OLEDGUI_H
#define __OLEDGUI_H 
#include "sys.h"

void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(int x1,int y1,int x2,int y2,int color);
void OLED_DrawRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(int x, int y, int r, int color);
void OLED_Refresh_GRAM(uint8_t op);
void OLED_Clean_GRAM(uint8_t t);
void loading(void);
void SHOW_CG(void);
#endif

