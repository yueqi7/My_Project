#include "spi_oled.h"
#include "stdlib.h"
#include "stdarg.h"
#include "oledfont.h"  	
#include "bmp.h"

//OLED display memory
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
static uint8_t  SIZE=12;  //font size

/******************************************************************/
//	Description:	This function write a Byte to SSD1106
//	Author:			qi.yue
//	param:			u8 dat: what need to write
//					u8 cmd: flag of data or command
//							0:command; 1:data
//	Return:			void
//	Note:			void
/******************************************************************/
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
#ifdef USING_DC	
	if(cmd)
	  OLED_DC=1;
	else 
	  OLED_DC=0;	
	OLED_CS=0;
#endif 
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK=0;
		if(dat&0x80)
		   OLED_SDIN=1;
		else 
		   OLED_SDIN=0;
		OLED_SCLK=1;
		dat<<=1;   
	}				 		  
	OLED_CS=1;
#ifdef USING_CS	
	OLED_DC=1;   	  
#endif 
} 
/**************************************************/
//	Description:	This function 
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   
/**************************************************/
//	Description:	This function turn on the display
//	Author:			qi.yue
//	param:			void
//	Return:			void
//	Note:			you must call this function after
//					initializing ssd1106
/**************************************************/  
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC Command
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
/**************************************************/
//	Description:	This function turn off the display
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC Command
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
/**************************************************/
//	Description:	This function clean the display
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //setting page（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //setting display position - addr of low col
		OLED_WR_Byte (0x10,OLED_CMD);      //setting display position - addr of hagh col
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} 
}
/**************************************************/
//	Description:	This function show a character 
//					at specified position
//	Author:			qi.yue
//	param:			u8 x: x:0~127
//					u8 y: y:0~63
//					u8 chr:the character witch will be displayed
//					u8 mode : character color 0:black, 1:white
//	Return:			void
//	Note:			void
/**************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 mode)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';	
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i]^(0xff*mode),OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8]^(0xff*mode),OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i]^(0xff*mode),OLED_DATA);
			}
}
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

/**************************************************/
//	Description:	This function show a number
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/ 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',0); 
	}
} 
/**************************************************/
//	Description:	This function show a string
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/ 	
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 mode)
{
	unsigned char j=0;
	y-=2;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],mode);
		x+=(SIZE == 16)?8:6;
//		if(x>120){x=0;y+=2;}
		if(x>120)return;
			j++;
	}
}
/**************************************************/
//	Description:	This function show a Chinese word
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/ 	
void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 size)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<size;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<size;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
/**************************************************/
//	Description:	This function show a bmp picture
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/ 	
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

/**************************************************/
//	Description:	This function initionlized SSD1306
//	Author:			qi.yue
//	param:			
//	Return:			void
//	Note:			void
/**************************************************/ 	
//				    
void SPI_OLED_Init(void)
{ 	 	 
	GPIO_InitTypeDef 	MyGPIO;

	RCC_APB2PeriphClockCmd(RCC_SCLK_PORT, ENABLE );
	MyGPIO.GPIO_Pin 	= GPIO_Pin_SCLK;	
 	MyGPIO.GPIO_Mode 	= GPIO_Mode_Out_PP; 		 
	MyGPIO.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(SCKL_PORT, &MyGPIO);	
	OLED_SCLK  = 1;
	
	RCC_APB2PeriphClockCmd(RCC_SDIN_PORT, ENABLE );
	MyGPIO.GPIO_Pin 	= GPIO_Pin_SDIN;	
 	MyGPIO.GPIO_Mode 	= GPIO_Mode_Out_PP; 		 
	MyGPIO.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(SDIN_PORT, &MyGPIO);	
	OLED_SDIN  = 1;
	
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
	delay_ms(100);
	OLED_RST = 0;
	delay_ms(100);
	OLED_RST = 1; 
#endif
			  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
} 
///*
//功能：OLED打印
//x		：起始横坐标 0-127
//y		：起始行		 0-7
//mode：反白显示	 0：关闭	1：开启
//size：字体大小	 12：6*8		16：8*16
//*/
void OLED_Printf(uint8_t x,uint8_t y,uint8_t mode,uint16_t size ,const char *str ,...)
{
	va_list ap;
	int cnt;
	char val;
	SIZE=size;
	va_start(ap,str);

	va_arg(ap,int);
	va_end(ap);
}
/****************************Function of Drawing***************************************/
u8 OLED_GRAM[8][128];
/**************************************************************/
//	Description:	This function can draw a point
//	Author:			qi.yue
//	param:			u8 x,y:	position of the point
//					ut t:	1 : light on; 0 :light off
//	Return:			void
//	Note:			x 0~127; y,0~63
/**************************************************************/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=y/8;
	bx=y%8;
	temp=1<<bx;
	if(t)OLED_GRAM[pos][x]|=temp;
	else OLED_GRAM[pos][x]&=~temp;	    
}
/************************************************************/
//	Description:	This function can draw a line
//	Author:			qi.yue 
//	param:			int x1,y1:	starting point
//					int x2,y2:	ending point
//					int color:	the pixel light on or off,
//								on : 1, off : 0
//	Return:			void
//	Note:			x1,x2 0~127; y1,y2 0~63
/***********************************************************/
void OLED_DrawLine(int x1,int y1,int x2,int y2,int color)
{
    int dx,dy,e;
    dx=x2-x1; 
    dy=y2-y1;
    if(dx>=0)
    {
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 1/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){y1+=1;e-=dx;}   
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 2/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){x1+=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 8/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}   
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 7/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){x1+=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
    else //dx<0
    {
        dx=-dx;     //dx=abs(dx)
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 4/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){y1+=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}   
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)
            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}   
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    OLED_DrawPoint(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}   
                    y1-=1;
                    e+=dx;
                }
            }
        }   
    }
}
/**********************************************************/
//	Description:	This function can draw a circle. draw 1/8 of 
//					circle,then draw others parts based on symmetry
//	Author:			qi.yue 
//	param:			int x,y:	The position ot the center of the circle
//					int r:		the range of the circle
//					color:		the pixel light on or off,
//								on : 1, off : 0
//	Return:			void
//	Note:   ---------------->X
//          |(0,0)   0
//          |     7     1
//          |    6       2
//          |     5     3
//       (Y)V        4
//
//      L = x^2 + y^2 - r^2
/***********************************************************/
void OLED_DrawCircle(int x, int y, int r, int color)
{
    int a, b, num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)          // 1/8圆即可
    {
        OLED_DrawPoint(x + a, y - b,color); // 0~1
        OLED_DrawPoint(x - a, y - b,color); // 0~7
        OLED_DrawPoint(x - a, y + b,color); // 4~5
        OLED_DrawPoint(x + a, y + b,color); // 4~3
 
        OLED_DrawPoint(x + b, y + a,color); // 2~3
        OLED_DrawPoint(x + b, y - a,color); // 2~1
        OLED_DrawPoint(x - b, y - a,color); // 6~7
        OLED_DrawPoint(x - b, y + a,color); // 6~5
        
        a++;
        num = (a * a + b * b) - r*r;
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}

/**********************************************************/
//	Description:	This function can draw a rectangle
//	Author:			qi.yue 
//	param:			u8 x1,y1:	starting point
//					u8 x2,y2:	ending point
//					mode:		the pixel light on or off,
//								on : 1, off : 0
//	Return:			void
//	Note:			x,x0 0~127; Y,Y0 0~63
void OLED_DrawRectangle(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode)
{
	OLED_DrawLine(x1,y1,x2,y1,mode);
	OLED_DrawLine(x1,y1,x1,y2,mode);
	OLED_DrawLine(x2,y2,x2,y1,mode);
	OLED_DrawLine(x2,y2,x1,y2,mode);
}
void OLED_Refresh_GRAM(void)
{ 
 unsigned char x,y;
  
	for(y=0;y<7;y++)
	{
		OLED_Set_Pos(0,y);
    for(x=0;x<127;x++)
	    {      
	    	OLED_WR_Byte(OLED_GRAM[y][x],OLED_DATA);	    	
	    }
	}
}
/**********************************************************/
//	Description:	This function will clean the anaiog 
//					Oled memory OLED_GRAM[8][128]
//	Author:			qi.yue
//	param:			void
//	Return:			void
//	Note:			None
/*********************************************************/

void OLED_Clean_GRAM(void)
{
 unsigned char x,y;
 
	for(y=0;y<7;y++)
    for(x=0;x<127;x++)         
				OLED_GRAM[y][x]=0;	    	
}
/**********************************************************/
//	Description:	This function will draw a grid on OLED
//	Author:			qi.yue
//	param:			char x0:	initial x position 0~127
//					char y0:	initial y position 0~63
//					char col:	the grid's columns
//					char lin:	the grid's lines
//					char size:	the size of every grid
//	Return:			void
//	Note:			None
/*********************************************************/
void Draw_Grid(char x0,char y0,char x,char y,char n)
{



}