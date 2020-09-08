#include <key.h>

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//开启GPIOB时钟
    GPIO_Structure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Structure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_Structure);	//初始化 PB1 PB2 PB3 PB4 
		
}

