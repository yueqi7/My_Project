#include "sys.h"


int main(void)
{
	uint32_t i=0,j=0,Hour_Start=8;
	delay_init();	//��ʱ������ʼ��
//	Key_Init();		//������ʼ��
//	LED_Init();
	SPIx_Init(SPI1);//Ĭ������
	OLED_Init(SPI1,BLACK);
	while (1)
	{
		Show_ClkNum(Hour_Start+00 ,2,00,1);
		Show_ClkNum(Hour_Start+20 ,2,01,1);
		Show_ClkNum(Hour_Start+40 ,2,10,1);
		Show_ClkNum(Hour_Start+50 ,2,03,1);
		Show_ClkNum(Hour_Start+70 ,2,05,1);
		Show_ClkNum(Hour_Start+90 ,4,10,0);
		Show_ClkNum(Hour_Start+95 ,4,02,0);
		Show_ClkNum(Hour_Start+105,4,03,0);
	
	}
}
