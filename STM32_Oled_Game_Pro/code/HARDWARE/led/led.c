#include "led.h"

//移植请修改头文件宏定义

void LED_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /***************************LED0初始化***********************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED, ENABLE); //使能LED0连接端口时钟  /
    GPIO_InitStructure.GPIO_Pin = Pin_LED;              //LED0端口配置					 /
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出							 /
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz				 /
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);           //根据设定参数初始化LED0/
                                                        /************************************************************************************/
    LED = LED_OFF;                                      //关闭LED
}
