#include "sys.h"
extern unsigned char BMP3[];

int main(void)
{
	delay_init();	//��ʱ������ʼ��
//	Key_Init();		//������ʼ��
//	LED_Init();
	MySPI_Init();
	OLED_Init();
	while (1)
	{

	}
}
