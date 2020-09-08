#include "sys.h"
extern unsigned char BMP3[];

int main(void)
{int i=0;
	delay_init();	//延时函数初始化
//	Key_Init();		//按键初始化
//	LED_Init();
	SPI_OLED_Init();
//	OLED_Init();//显式初始化
	while (1)
	{

		OLED_DrawLine(0	+i,0 ,32+i,6,1);
		OLED_DrawLine(32+i,6 ,44+i,23,1);
		OLED_DrawLine(44+i,23,23+i,56,1);
		OLED_DrawLine(23+i,56,0 +i,0,1);
		i++;
		OLED_Refresh_GRAM();
		OLED_Clean_GRAM();
	}
}
