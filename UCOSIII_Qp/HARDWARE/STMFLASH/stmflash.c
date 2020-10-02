#include "stmflash.h"
/*
���ܣ���ָ����ַд������
����˵����addr д���FLASHҳ���׵�ַ
          p    ��д������ĵ�ַ�������еı�����uint8_t���ͣ�Ԫ�ظ���������ż����
          Byte_Num ��д��������ֽ�����������ż����
*/
void FLASH_WriteByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num)
{
	uint32_t HalfWord;
	Byte_Num = Byte_Num/2;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(addr);
	while(Byte_Num --)
	{
		HalfWord=*(p++);
		HalfWord|=*(p++)<<8;
		FLASH_ProgramHalfWord(addr, HalfWord);
		addr += 2;
	}
	FLASH_Lock();
}



/*
���ܣ���ָ����ַ��ȡ����
����˵����addr ��FLASH�ж�ȡ�ĵ�ַ
          p    ��ȡ��Ҫ��������ĵ�ַ�������еı�����uint8_t���ͣ�
          Byte_Num Ҫ�������ֽ���
*/

void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num)
{
  while(Byte_Num--)
  {
   *(p++)=*((uint8_t*)addr++);
  }
}

/*
���ܣ���ָ��ҳд��ֱ�Ӹ���
����˵����PageNum 	д�����ݵ�ҳ��
          buf    		Ҫ��������ĵ�ַ�������еı�����uint8_t���ͣ�
          count			Ҫд����ֽ���
*/
void Flash_Write_Page(uint8_t PageNum,uint8_t *buf,uint16_t count)
{
	if(count>1024)count=1024;
	FLASH_WriteByte(StartAddr+1024*PageNum,buf,count);
}



