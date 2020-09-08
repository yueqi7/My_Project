#include "iic_drv.h"

/*
*�ײ�����io����
*/
#ifdef STM32
GPIO_InitTypeDef GPIO_InitStr;
void IIC_Init(void)

{
/****************************IIC_SDA��ʼ��***********************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDA_PORT, ENABLE);	//ʹ��SDA���Ӷ˿�ʱ��   /
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_SDA;										//SDA�˿�����					   /
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//�������							 /
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;							//IO���ٶ�Ϊ50MHz				 /
	GPIO_Init(GPIO_SDA_PORT, &GPIO_InitStr);					 			//�����趨������ʼ��SDA /
/****************************IIC_SCL��ʼ��***********************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SCL_PORT, ENABLE);	//ʹ��SCL���Ӷ˿�ʱ�� 	 /
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_SCL;										//SCL�˿�����						 /
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//�������							 /
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;							//IO���ٶ�Ϊ50MHz				 /
	GPIO_Init(GPIO_SCL_PORT, &GPIO_InitStr);					 			//�����趨������ʼ��SCL /
/****************************************************************************************/
 	SDA_HIGH();	  	  
	SCL_HIGH();
}

void SDA_IN(void)
{
    GPIO_InitStr.GPIO_Pin = GPIO_Pin_SDA;    //SDA�˿�����
    GPIO_InitStr.GPIO_Mode = GPIO_Mode_IPU;  //�������
    GPIO_Init(GPIO_SDA_PORT, &GPIO_InitStr); //�����趨������ʼ��SDA
}
void SDA_OUT(void)
{
    GPIO_InitStr.GPIO_Pin = GPIO_Pin_SDA;      //SCL�˿�����
    GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP; //�������
    GPIO_Init(GPIO_SDA_PORT, &GPIO_InitStr);   //�����趨������ʼ��SCL
}

void SCL_LOW(void) 	{ IIC_SCL = 0; }
void SCL_HIGH(void) { IIC_SCL = 1; }
void SDA_LOW(void) 	{ IIC_SDA = 0; }
void SDA_HIGH(void) { IIC_SDA = 1; }
void IIC_Delay_us(int nus)
{
   	delay_us(nus);
}
void IIC_Delay_ms(int nms)
{
	delay_ms(nms);
}
#endif

#ifdef C51

void IIC_Init()
{
    //��֤���߿���
    SCL_HIGH();
    SDA_HIGH();
}
void SDA_IN(void) {}

void SDA_OUT(void) {}

void SCL_LOW(void) 	{ IIC_SCL = 0; }
void SCL_HIGH(void) { IIC_SCL = 1; }
void SDA_LOW(void) 	{ IIC_SDA = 0; }
void SDA_HIGH(void) { IIC_SDA = 1; }
void IIC_Delay_us(int nus)
{
    //	do
    //	{
    //		_nop_();
    //	}while(--nus);
}
void IIC_Delay_ms(int nms)
{
    unsigned char i, j;
    do
    {
        i = 2;
        j = 239;
        do
        {while (--j);     
        } while (--i);
    }while (--nms);
}
#endif
