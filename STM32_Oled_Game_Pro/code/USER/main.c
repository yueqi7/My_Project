#include "sys.h"
extern unsigned char BMP3[];

int main(void)
{
	delay_init();	//延时函数初始化
//	Key_Init();		//按键初始化
//	LED_Init();
	MySPI_Init();
	OLED_Init();
	while (1)
	{

	}
}
