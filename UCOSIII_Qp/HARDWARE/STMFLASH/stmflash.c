#include "stmflash.h"
/*
功能：向指定地址写入数据
参数说明：addr 写入的FLASH页的首地址
          p    被写入变量的地址（数组中的必须是uint8_t类型，元素个数必须是偶数）
          Byte_Num 被写入变量的字节数（必须是偶数）
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
功能：从指定地址读取数据
参数说明：addr 从FLASH中读取的地址
          p    读取后要存入变量的地址（数组中的必须是uint8_t类型）
          Byte_Num 要读出的字节数
*/

void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num)
{
  while(Byte_Num--)
  {
   *(p++)=*((uint8_t*)addr++);
  }
}

/*
功能：从指定页写入直接覆盖
参数说明：PageNum 	写入数据的页码
          buf    		要存入变量的地址（数组中的必须是uint8_t类型）
          count			要写入的字节数
*/
void Flash_Write_Page(uint8_t PageNum,uint8_t *buf,uint16_t count)
{
	if(count>1024)count=1024;
	FLASH_WriteByte(StartAddr+1024*PageNum,buf,count);
}



