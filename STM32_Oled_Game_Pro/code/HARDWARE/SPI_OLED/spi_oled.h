#ifndef __SPI_OLED_H__
#define	__SPI_OLED_H__
#include "sys.h"                  
#define USING_RST
#define USING_DC


//IO Definitions
#define 	SCKL_PORT				GPIOB
#define 	RCC_SCLK_PORT 	RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_SCLK		GPIO_Pin_11
#define		OLED_SCLK				PBout(11)

#define 	SDIN_PORT				GPIOB
#define 	RCC_SDIN_PORT 	RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_SDIN		GPIO_Pin_12
#define		OLED_SDIN				PBout(12)

#ifdef USING_RST	
#define 	RST_PORT				GPIOB
#define 	RCC_RST_PORT 		RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_RST		GPIO_Pin_13
#define		OLED_RST				PBout(13)
#endif	

#ifdef USING_DC	
#define 	DC_PORT					GPIOB
#define 	RCC_DC_PORT 		RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_DC			GPIO_Pin_14
#define		OLED_DC					PBout(14)
#endif
	

#define 	CS_PORT					GPIOB
#define 	RCC_CS_PORT 		RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_CS			GPIO_Pin_15
#define		OLED_CS					PBout(15)


#define Max_Column	128
#define Max_Row			64
#define	Brightness	0xFF 
#define X_WIDTH 		128
#define Y_WIDTH 		64	    
#define OLED_CMD  	0	//§Õ????
#define OLED_DATA 	1	//§Õ????

//OLED?????¨²???
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 mode);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 size);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void SPI_OLED_Init(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(int x1,int y1,int x2,int y2,int color);
void OLED_DrawCircle(int x, int y, int r, int color);
void OLED_DrawRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_Refresh_GRAM(void);
void OLED_Clean_GRAM(void);
#endif

