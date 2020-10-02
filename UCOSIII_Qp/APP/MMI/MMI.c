#include "mmi.h"
#include "bmp.h"  
#include "u8g2.h"
#include "u8x8.h"
#include "u8g2_arm.h"
u8g2_t u8g2;
u8x8_t u8x8;

void MMI_task(void *p_arg)
{
	uint8_t Hour_Start=8;
	uint8_t i=0;
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2,U8G2_R2,u8x8_byte_hw_spi,u8g2_gpio_and_delay_stm32);
  u8x8_InitDisplay(u8g2_GetU8x8(&u8g2));
//	SHOW_CG();
//	OLED_Display_On(); /*display ON*/

//		Show_ClkNum(Hour_Start+00 ,2,00,1);
//		Show_ClkNum(Hour_Start+20 ,2,01,1);
//		Show_ClkNum(Hour_Start+40 ,2,10,1);
//		Show_ClkNum(Hour_Start+50 ,2,03,1);
//		Show_ClkNum(Hour_Start+70 ,2,05,1);
//		Show_ClkNum(Hour_Start+90 ,4,10,0);
//		Show_ClkNum(Hour_Start+95 ,4,02,0);
//		Show_ClkNum(Hour_Start+105,4,03,0);
//	OLED_ShowString("");

//	OLED_Clear(0xff);
//  u8g2_FirstPage(&u8g2);

  do
  {      
    u8g2_SetFontMode(&u8g2, 1);	// Transparent
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(&u8g2, 0, 30, "U");
    
    u8g2_SetFontDirection(&u8g2, 1);
    u8g2_SetFont(&u8g2, u8g2_font_inb30_mn);
    u8g2_DrawStr(&u8g2, 21,8,"8");
        
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(&u8g2, 51,30,"g");
    u8g2_DrawStr(&u8g2, 67,30,"\xb2");
    
    u8g2_DrawHLine(&u8g2, 0, 40, 45);
    u8g2_DrawHLine(&u8g2, 1, 41, 45);
    u8g2_DrawVLine(&u8g2, 40, 35, 10);
    u8g2_DrawVLine(&u8g2, 41, 36, 10);
		delay_ms(10);
  } while( u8g2_NextPage(&u8g2) );
   
	
}


void SHOW_CG(void)
{
	signed char x1=63,y1=31,x2=64,y2=32,i;
	
	for(i=0;i<4;i++){
		show_loading(1,1,44);
		OLED_ShowString(32,7,"Loading .",0);
		delay_ms(200);

		show_loading(2,1,44);
		OLED_ShowString(32,7,"Loading ..",0);
		delay_ms(200);

		show_loading(3,1,44);
		OLED_ShowString(32,7,"Loading ...",0);
		delay_ms(200);

		show_loading(2,1,44);
		OLED_ShowString(32,7,"Loading    ",0);
		delay_ms(200);
	}
	do
	{
		OLED_DrawRectangle(x1,y1,x2,y2,0);
		OLED_DrawRectangle(x1-1,y1,x2+1,y2,0);
		OLED_Refresh_GRAM(0);
		delay_ms(2);
		x1-=2;y1--;x2+=2;y2++;
	}while(x1>0);
}


void show_loading(u8 count,u8 start_lin,u8 start_col)// 1 44
{
	signed char i,j,k;
	u8 *p;

		for(i=0;i<5;i++)
		{
			p=&OLED_GRAM[start_lin+i][start_col];
				for (j=0;j<40;j++,p++)
				{
					switch (count)
					{
						case 1:*p=(LOAD1[i][j]);break;
						case 2:*p=(LOAD2[i][j]);break;
						case 3:*p=(LOAD3[i][j]);break;
						default :break;
					}
				}
		}	
		OLED_Refresh_GRAM(0);

}



