#include "oledgui.h"
#include "oledfont.h"  

extern void OLED_Set_Pos(unsigned char x, unsigned char y) ;
/**************************************************/
//u8 x: x:0~127
//u8 y: y:0~63
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 back_mode)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';	
		if(x>Max_Column-1){x=0;y=y+2;}
		OLED_Set_Pos(x,y);	

		for(i=0;i<6;i++)
		OLED_Write(F6x8[c][i]^(0xff*back_mode),OLED_DATA);
}

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 back_mode)
{
	unsigned char j=0;

	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],back_mode);
			x+=6;
			if(x>120){x=0;y+=2;}
			j++;
	}
}

void OLED_ShowCHinese(u8 x,u8 y,u8 no,u8 size)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<size;t++)
		{
				OLED_Write(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<size;t++)
			{	
				OLED_Write(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
///***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
//{ 	
// unsigned int j=0;
// unsigned char x,y;
//  
//  if(y1%8==0) y=y1/8;      
//  else y=y1/8+1;
//	for(y=y0;y<y1;y++)
//	{
//		OLED_Set_Pos(x0,y);
//    for(x=x0;x<x1;x++)
//	    {      
//	    	OLED_Write(BMP[j++],OLED_DATA);	    	
//	    }
//	}
//} 
void Show_ClkNum(uint8_t x,uint8_t y,char n,char font)
{
	char i,j,line;
	char *p=NULL;

	if(font) 
	{
		line=4;
		p=Clock_Num20X32[line*n];
	}
	else
	{		
		line=2;
		p=Clock_Num10X16[line*n];
	}
	
		for(i=line*n;i<n*line+line;i++,y++)
		{
			OLED_Set_Pos(x,y);
			for (j=0;j<5*line/(n/10+1);j++,p++)
			{
				OLED_Write(*p,OLED_DATA);
			}
		}
}
/******************************以上无需缓存************************************************/

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
void OLED_DrawBMP(uint8_t pos_x,uint8_t pos_y,uint8_t size_x,uint8_t size_y,uint8_t addr[])
{
 unsigned int j=0;
 unsigned char x,y;
  
  if(size_y%8==0) size_y=size_y/8;      
  else size_y=size_y/8+1;
	for(y=pos_y;y<pos_y+size_y;y++)
	{
    for(x=pos_x;x<size_x;x++,addr++)
	    { 
				OLED_GRAM[y][x]=*addr;					
	    }
	}


}
void OLED_Refresh_GRAM(uint8_t op)
{ 
 unsigned char x,y;
  
	if(op)op=0xff;
	for(y=0;y<8;y++)
	{
		OLED_Set_Pos(0,y);
    for(x=0;x<128;x++)
	    {      
	    	OLED_Write(OLED_GRAM[y][x]^op,OLED_DATA);	    	
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

void OLED_Clean_GRAM(uint8_t t)
{
	memset(OLED_GRAM,t,8*128);	
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
//void Draw_Grid(char x0,char y0,char x,char y,char n)
//{



//}
