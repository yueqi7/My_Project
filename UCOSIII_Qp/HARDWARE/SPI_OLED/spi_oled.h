#ifndef __SPI_OLED_H__
#define	__SPI_OLED_H__
#include "sys.h"

#define USING_RST
#define USING_DC



#ifdef USING_RST	
#define 	RST_PORT				GPIOB
#define 	RCC_RST_PORT 		RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_RST		GPIO_Pin_10
#define		OLED_RST				PBout(10)
#endif	

#ifdef USING_DC	
#define 	DC_PORT					GPIOB
#define 	RCC_DC_PORT 		RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_DC			GPIO_Pin_1
#define		OLED_DC					PBout(1)
#endif

#define 	CS_PORT					GPIOB
#define 	RCC_CS_PORT 		RCC_APB2Periph_GPIOB
#define 	GPIO_Pin_CS			GPIO_Pin_0
#define		OLED_CS					PBout(0)


   
#define OLED_CMD  	0
#define OLED_DATA 	1
#define BLACK				0
#define WHITE				1

void OLED_Write(uint8_t data,uint8_t mode);
void OLED_Init(SPI_TypeDef* SPIx,uint8_t back_mode);
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Clear(uint8_t back_mode);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;

#endif

