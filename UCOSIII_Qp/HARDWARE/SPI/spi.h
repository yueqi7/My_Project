#ifndef __SPI_H__
#define	__SPI_H__
#include "sys.h"
#include "stdbool.h"

void 	SPI_IO_EN(SPI_TypeDef* SPIx);
void SPIx_Init(SPI_TypeDef* SPIx );
uint8_t SPI_ReadWriteByte(SPI_TypeDef* SPIx,uint8_t spi_byte);
#endif
