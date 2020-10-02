#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x_flash.h" 

//С������Ʒ���洢��1-32KB�� ÿҳ1KB��
//��������Ʒ���洢��64-128KB�� ÿҳ1KB��
//��������Ʒ���洢��256KB���ϣ� ÿҳ2KB��
//�����Ͳ�Ʒ���洢��256KB���ϣ� ÿҳ2KB��
//д����ʱ�������ҳ�������ݣ��粢��ȫ������һ��Ҫ�ȶ�ȡ��д��

#define BaseAddr 			0x8000000	//�����޸�
#define StartAddr			BaseAddr +  32*1024  //32kλ��	


void FLASH_WriteByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void Flash_Write_Page(uint8_t PageNum,uint8_t *buf,uint16_t count);

#endif

















