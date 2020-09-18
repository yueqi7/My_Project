#include "oledgui.h"

extern unsigned char LOAD1[];
extern unsigned char LOAD2[];
extern unsigned char LOAD3[];

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
	if(x>127||y>63)return;//³¬³ö·¶Î§ÁË.
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
    while(2 * b * b >= r * r)          // 1/8Ô²¼´¿É
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
	memset(&OLED_GRAM[0][0],t,8*128);	
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
void SHOW_CG(void)
{
	signed char x1=63,y1=31,x2=64,y2=32,i;
	loading();
	do
	{
		OLED_DrawRectangle(x1,y1,x2,y2,1);
		OLED_DrawRectangle(x1-1,y1,x2+1,y2,1);
		OLED_Refresh_GRAM(1);
		delay_ms(10);
		x1-=2;y1--;x2+=2;y2++;
	}while(x1>0);
}

char start_lin=1;
char start_col=44;
void loading(void)
{
	signed char i,j;
	for(i=0;i<17;i++)
	{
		for(j=0;j<5;j++)
		{
			if(i%2==0)						memcpy(&OLED_GRAM[start_lin+j][start_col],LOAD2+j*40,40);
			else if((i+1)%4==0)		memcpy(&OLED_GRAM[start_lin+j][start_col],LOAD1+j*40,40);		
			else									memcpy(&OLED_GRAM[start_lin+j][start_col],LOAD3+j*40,40);
		}
		OLED_Refresh_GRAM(1);
		delay_ms(100);
	}
}