//本程序只供学习使用，未经作者许可，不得用于其它任何用途//
//
//
/******************说明********************
*作者：月祺
*用于多平台移植使用的iic总线协议
*目前已支持STM  C51
*已测试外设 0.96寸OLED  MPU6050
*移植请修改 驱动头文件 标注处宏定义
*如果需要延时请移步 驱动C文件 添加或修改延时函数
*时间：2020.1.14
*版本：V2.0
*更新说明：iic协议ACK部分钳住总线在做应答
*部分器件非标准iic协议 请针对时序修改
*****************************************/
#ifndef __IIC_H
#define __IIC_H
#include "IIC_drv.h"

/*
*IIC协议函数
*/
void IIC_Start(void);
void IIC_Stop(void);
void IIC_ACK(void);
void IIC_NACK(void);
unsigned char IIC_Wait_Ack(void);
unsigned char IIC_Read_Byte(unsigned char Ack_EN);
unsigned char IIC_Read_Data(unsigned char Device_addr, unsigned char Reg_addr, unsigned char ACK_EN);
void IIC_Write_Byte(unsigned char DATA);
void IIC_Write_Data(unsigned char Device_addr, unsigned char Reg_addr, unsigned char DATA);

#endif
