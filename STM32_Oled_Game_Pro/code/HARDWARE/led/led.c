#include "led.h"

//��ֲ���޸�ͷ�ļ��궨��

void LED_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /***************************LED0��ʼ��***********************************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED, ENABLE); //ʹ��LED0���Ӷ˿�ʱ��  /
    GPIO_InitStructure.GPIO_Pin = Pin_LED;              //LED0�˿�����					 /
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //�������							 /
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO���ٶ�Ϊ50MHz				 /
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);           //�����趨������ʼ��LED0/
                                                        /************************************************************************************/
    LED = LED_OFF;                                      //�ر�LED
}
