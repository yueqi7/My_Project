//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;//
//
//
/******************˵��********************
*���ߣ�����
*���ڶ�ƽ̨��ֲʹ�õ�iic����Э��
*Ŀǰ��֧��STM  C51
*�Ѳ������� 0.96��OLED  MPU6050
*��ֲ���޸� ����ͷ�ļ� ��ע���궨��
*�����Ҫ��ʱ���Ʋ� ����C�ļ� ��ӻ��޸���ʱ����
*ʱ�䣺2020.1.14
*�汾��V2.0
*����˵����iicЭ��ACK����ǯס��������Ӧ��
*���������Ǳ�׼iicЭ�� �����ʱ���޸�
*****************************************/
#ifndef __IIC_H
#define __IIC_H
#include "IIC_drv.h"

/*
*IICЭ�麯��
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
