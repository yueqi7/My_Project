#ifndef __SPI_H__
#define	__SPI_H__
#include "sys.h"

#define USING_SPI1

#ifdef USING_SPI1
#define MYSPI						SPI1
#define RCC_SPI					RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE );//MYSPI ±÷” πƒ‹ 	
#define RCC_GPIO				RCC_APB2Periph_GPIOA
#define SPI_GPIO_PORT		GPIOA
#define SPI_SCLK_IO			GPIO_Pin_5
#define SPI_MISO_IO			GPIO_Pin_6
#define SPI_MOSI_IO			GPIO_Pin_7
#endif

void MySPI_Init(void);
uint8_t SPI_ReadWriteByte(uint8_t spi_byte);
#endif
