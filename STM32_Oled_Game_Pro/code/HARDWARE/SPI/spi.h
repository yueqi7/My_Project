#ifndef __SPI_H__
#define	__SPI_H__
#include "stm32f10x_rcc.h"
#include "stdbool.h"

bool 	SPI_IO_EN(SPI_TypeDef* SPIx);
bool SPIx_Init(SPI_TypeDef* SPIx );
uint8_t SPI_ReadWriteByte(SPI_TypeDef* SPIx,uint8_t spi_byte);
#endif
