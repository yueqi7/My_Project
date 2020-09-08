//本程序只供学习使用，未经作者许可，不得用于其它任何用途//

/******************说明********************
*作者：月祺
*版本：V 1.0
*用于多平台移植的iic总线协议底层驱动
*目前支持STM  C51
*移植请修改标注处宏定义
*如果需要延时请移步驱动C文件添加或修改延时函数
*时间：2020.1.14
*****************************************/


#ifndef __IIC_DRV_H
#define __IIC_DRV_H	 

#define STM32			/*宏定义修改处*/
/*
*STM32使用
*/
#ifdef STM32
#include "sys.h"		/*不同芯片请修改对应头文件*/
extern GPIO_InitTypeDef  GPIO_InitStr;						  

#define RCC_APB2Periph_SCL_PORT			RCC_APB2Periph_GPIOB	/*宏定义修改处*/
#define GPIO_SCL_PORT								GPIOC                 /*宏定义修改处*/
#define GPIO_Pin_SCL								GPIO_Pin_10            /*宏定义修改处*/

#define RCC_APB2Periph_SDA_PORT			RCC_APB2Periph_GPIOB	/*宏定义修改处*/
#define GPIO_SDA_PORT								GPIOC									/*宏定义修改处*/
#define GPIO_Pin_SDA								GPIO_Pin_11						/*宏定义修改处*/


#define IIC_SCL								PCout(10)//SCL               /*宏定义修改处*/
#define IIC_SDA								PCout(11)//SDA               /*宏定义修改处*/
#define	READ_SDA							PCin(11)	//SDA状态读取       /*宏定义修改处*/
#endif

/*
*C51使用 
*/
#ifdef C51
#include "reg52.h"

sbit IIC_SCL = P4^1;  /*宏定义修改处*/
sbit IIC_SDA = P4^0;  /*宏定义修改处*/

#define READ_SDA		 IIC_SDA	//读取IIC数据线电平
#endif

/*
*IIC驱动IO函数
*/
void IIC_Init(void);
void SCL_LOW(void);
void SCL_HIGH(void);
void SDA_LOW(void);
void SDA_HIGH(void);
void SDA_IN(void);
void SDA_OUT(void);
void IIC_Delay_us(int nus);			/*延时函数*/
void IIC_Delay_ms(int nms);			/*延时函数*/

#endif
