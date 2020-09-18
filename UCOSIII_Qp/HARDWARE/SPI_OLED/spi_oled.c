#include <stdlib.h>  	
#include "spi_oled.h"
#include "spi.h" 
#include "delay.h"  	


static  SPI_TypeDef* OLED_SPI=NULL;

void OLED_Write(uint8_t data,uint8_t DC_mode)
{
	OLED_CS=0;
	OLED_DC=DC_mode;
	SPI_ReadWriteByte(OLED_SPI,data);
	OLED_CS=1;
}
/**************************************************/
//	Description:	This function initionlized SSD1306
//	Author:			qi.yue
//	param:			choose the SPI for OLED; if mode=0,
//							oled will clear to light off,else on.
/**************************************************/ 	
void OLED_Init(SPI_TypeDef* SPIx,uint8_t back_mode)
{ 	 	 
	GPIO_InitTypeDef 	MyGPIO;
	OLED_SPI=SPIx;

#ifdef USING_DC
	RCC_APB2PeriphClockCmd(RCC_DC_PORT, ENABLE );
	MyGPIO.GPIO_Pin 	= GPIO_Pin_DC;	
 	MyGPIO.GPIO_Mode 	= GPIO_Mode_Out_PP; 		 
	MyGPIO.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(DC_PORT, &MyGPIO);	
	OLED_DC  = 1;
#endif
	RCC_APB2PeriphClockCmd(RCC_CS_PORT, ENABLE );
	MyGPIO.GPIO_Pin 	= GPIO_Pin_CS;	
 	MyGPIO.GPIO_Mode 	= GPIO_Mode_Out_PP; 		 
	MyGPIO.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(CS_PORT, &MyGPIO);	  
	OLED_CS	 = 1;
	#ifdef USING_RST
	RCC_APB2PeriphClockCmd(RCC_RST_PORT, ENABLE );
	MyGPIO.GPIO_Pin 	= GPIO_Pin_RST;	
 	MyGPIO.GPIO_Mode 	= GPIO_Mode_Out_PP; 		 
	MyGPIO.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(RST_PORT, &MyGPIO);
	OLED_RST = 1;
	delay_ms(200);
	OLED_RST = 0;
	delay_ms(200);
	OLED_RST = 1;
#endif

	OLED_Write(0xAE,OLED_CMD);//--turn off oled panel
	OLED_Write(0x00,OLED_CMD);//---set low column address
	OLED_Write(0x10,OLED_CMD);//---set high column address
	OLED_Write(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write(0x81,OLED_CMD);//--set contrast control register
	OLED_Write(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_Write(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_Write(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_Write(0xA6,OLED_CMD);//--set normal display
	OLED_Write(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_Write(0x3f,OLED_CMD);//--1/64 duty
	OLED_Write(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write(0x00,OLED_CMD);//-not offset
	OLED_Write(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_Write(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write(0xD9,OLED_CMD);//--set pre-charge period
	OLED_Write(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_Write(0x12,OLED_CMD);
	OLED_Write(0xDB,OLED_CMD);//--set vcomh
	OLED_Write(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_Write(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write(0x02,OLED_CMD);//
	OLED_Write(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_Write(0x14,OLED_CMD);//--set(0x10) disable
	OLED_Write(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Write(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_Display_On(); /*display ON*/
	OLED_Clear(back_mode);

}

/**************************************************/
//	Note:	you must call this function after
//				initializing ssd1106
/**************************************************/
void OLED_Display_On(void)
{
	OLED_Write(0X8D,OLED_CMD);  //SET DCDC Command
	OLED_Write(0X14,OLED_CMD);  //DCDC ON
	OLED_Write(0XAF,OLED_CMD);  //DISPLAY ON
}
void OLED_Display_Off(void)
{
	OLED_Write(0X8D,OLED_CMD);  //SET DCDC Command
	OLED_Write(0X10,OLED_CMD);  //DCDC OFF
	OLED_Write(0XAE,OLED_CMD);  //DISPLAY OFF
}

/**************************************************/
//	Note:	mode 0,clear to black,
//						 1,clear to white
/**************************************************/
void OLED_Clear(uint8_t back_mode)  
{  
	u8 i,n;
	if(back_mode)back_mode=0xff;
	for(i=0;i<8;i++)  
	{  
		OLED_Write (0xb0+i,OLED_CMD);    //setting page（0~7）
		OLED_Write (0x00,OLED_CMD);      //setting display position - addr of low col
		OLED_Write (0x10,OLED_CMD);      //setting display position - addr of hagh col
		for(n=0;n<128;n++)OLED_Write(back_mode,OLED_DATA); 
	} 
}


/**************************************************/
//u8 x: x:0~127
//u8 y: y:0~7
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_Write(0xb0+y,OLED_CMD);
	OLED_Write(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_Write((x&0x0f),OLED_CMD); 
} 

