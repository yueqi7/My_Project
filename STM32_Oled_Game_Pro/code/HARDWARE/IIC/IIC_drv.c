#include "iic_drv.h"

/*
*底层驱动io配置
*/
#ifdef STM32
GPIO_InitTypeDef GPIO_InitStr;
void IIC_Init(void)

{
/****************************IIC_SDA初始化***********************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDA_PORT, ENABLE);	//使能SDA连接端口时钟   /
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_SDA;										//SDA端口配置					   /
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出							 /
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;							//IO口速度为50MHz				 /
	GPIO_Init(GPIO_SDA_PORT, &GPIO_InitStr);					 			//根据设定参数初始化SDA /
/****************************IIC_SCL初始化***********************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SCL_PORT, ENABLE);	//使能SCL连接端口时钟 	 /
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_SCL;										//SCL端口配置						 /
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP; 		 					//推挽输出							 /
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;							//IO口速度为50MHz				 /
	GPIO_Init(GPIO_SCL_PORT, &GPIO_InitStr);					 			//根据设定参数初始化SCL /
/****************************************************************************************/
 	SDA_HIGH();	  	  
	SCL_HIGH();
}

void SDA_IN(void)
{
    GPIO_InitStr.GPIO_Pin = GPIO_Pin_SDA;    //SDA端口配置
    GPIO_InitStr.GPIO_Mode = GPIO_Mode_IPU;  //推挽输出
    GPIO_Init(GPIO_SDA_PORT, &GPIO_InitStr); //根据设定参数初始化SDA
}
void SDA_OUT(void)
{
    GPIO_InitStr.GPIO_Pin = GPIO_Pin_SDA;      //SCL端口配置
    GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_Init(GPIO_SDA_PORT, &GPIO_InitStr);   //根据设定参数初始化SCL
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
    //保证总线空闲
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
