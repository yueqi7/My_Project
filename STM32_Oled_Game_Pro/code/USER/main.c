#include "sys.h"
extern unsigned char BMP3[];

int main(void)
{
	int i=0,j=0;
	delay_init();	//��ʱ������ʼ��
//	Key_Init();		//������ʼ��
//	LED_Init();
	SPIx_Init(SPI1);//Ĭ������
	OLED_Init(SPI1,0);
	while (1)
	{
		for(i=0;i<=127;i+=2)
		{
			for(j=0;j<=63;j+=2)
			{
				OLED_DrawPoint(i,j,1);
				OLED_Refresh_GRAM();
				OLED_Clean_GRAM();
			}
		}
	}
}
