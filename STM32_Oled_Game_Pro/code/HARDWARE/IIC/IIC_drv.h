//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;//

/******************˵��********************
*���ߣ�����
*�汾��V 1.0
*���ڶ�ƽ̨��ֲ��iic����Э��ײ�����
*Ŀǰ֧��STM  C51
*��ֲ���޸ı�ע���궨��
*�����Ҫ��ʱ���Ʋ�����C�ļ���ӻ��޸���ʱ����
*ʱ�䣺2020.1.14
*****************************************/


#ifndef __IIC_DRV_H
#define __IIC_DRV_H	 

#define STM32			/*�궨���޸Ĵ�*/
/*
*STM32ʹ��
*/
#ifdef STM32
#include "sys.h"		/*��ͬоƬ���޸Ķ�Ӧͷ�ļ�*/
extern GPIO_InitTypeDef  GPIO_InitStr;						  

#define RCC_APB2Periph_SCL_PORT			RCC_APB2Periph_GPIOB	/*�궨���޸Ĵ�*/
#define GPIO_SCL_PORT								GPIOC                 /*�궨���޸Ĵ�*/
#define GPIO_Pin_SCL								GPIO_Pin_10            /*�궨���޸Ĵ�*/

#define RCC_APB2Periph_SDA_PORT			RCC_APB2Periph_GPIOB	/*�궨���޸Ĵ�*/
#define GPIO_SDA_PORT								GPIOC									/*�궨���޸Ĵ�*/
#define GPIO_Pin_SDA								GPIO_Pin_11						/*�궨���޸Ĵ�*/


#define IIC_SCL								PCout(10)//SCL               /*�궨���޸Ĵ�*/
#define IIC_SDA								PCout(11)//SDA               /*�궨���޸Ĵ�*/
#define	READ_SDA							PCin(11)	//SDA״̬��ȡ       /*�궨���޸Ĵ�*/
#endif

/*
*C51ʹ�� 
*/
#ifdef C51
#include "reg52.h"

sbit IIC_SCL = P4^1;  /*�궨���޸Ĵ�*/
sbit IIC_SDA = P4^0;  /*�궨���޸Ĵ�*/

#define READ_SDA		 IIC_SDA	//��ȡIIC�����ߵ�ƽ
#endif

/*
*IIC����IO����
*/
void IIC_Init(void);
void SCL_LOW(void);
void SCL_HIGH(void);
void SDA_LOW(void);
void SDA_HIGH(void);
void SDA_IN(void);
void SDA_OUT(void);
void IIC_Delay_us(int nus);			/*��ʱ����*/
void IIC_Delay_ms(int nms);			/*��ʱ����*/

#endif
