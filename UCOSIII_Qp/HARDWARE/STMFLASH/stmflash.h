#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x_flash.h" 

//小容量产品主存储块1-32KB， 每页1KB。
//中容量产品主存储块64-128KB， 每页1KB。
//大容量产品主存储块256KB以上， 每页2KB。
//互联型产品主存储块256KB以上， 每页2KB。
//写数据时会擦除该页所有数据，如并非全部覆盖一定要先读取再写入

#define BaseAddr 			0x8000000	//不可修改
#define StartAddr			BaseAddr +  32*1024  //32k位置	


void FLASH_WriteByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void Flash_Write_Page(uint8_t PageNum,uint8_t *buf,uint16_t count);

#endif

















