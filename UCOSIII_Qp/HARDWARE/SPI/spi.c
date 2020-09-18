#include "spi.h"
#include "usart.h"

static SPI_InitTypeDef  SPI_config={
	SPI_Direction_2Lines_FullDuplex,
	SPI_Mode_Master,
	SPI_DataSize_8b,
	SPI_CPOL_Low,
	SPI_CPHA_1Edge,
	SPI_NSS_Soft,
	SPI_BaudRatePrescaler_128,
	7
};	

void 	SPI_IO_EN(SPI_TypeDef* SPIx)
{    
	GPIO_InitTypeDef GPIO_Structure;
	
	GPIO_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	if(SPI1==SPIx){	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE );
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
		GPIO_Structure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
		GPIO_Init(GPIOA, &GPIO_Structure);
		GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	}
	else if	(SPI2==SPIx)	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,  ENABLE );
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
		GPIO_Structure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_Init(GPIOB, &GPIO_Structure);
		GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	} 
#ifdef STM32F10X_HD	
	else if (SPI3==SPIx)	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,  ENABLE );
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
		GPIO_Structure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
		GPIO_Init(GPIOB, &GPIO_Structure);
		GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5); 
	}	
#endif

}
//根据SPI_config配置SPIx若配置不同情先给SPI_config赋值再调用SPIx_Init()
void SPIx_Init(SPI_TypeDef* SPIx )
{
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
	SPI_IO_EN(SPIx);
	SPI_Init(SPIx, &SPI_config);
	SPI_Cmd(SPIx, ENABLE);
	printf("Init SPI ok.");
} 


uint8_t SPI_ReadWriteByte(SPI_TypeDef* SPIx,uint8_t spi_byte)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //TX_FIFO_EMPTY
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPIx, spi_byte); 
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //RX_FIFO_NOT_EMPTY
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPIx); //返回通过SPIx最近接收的数据			
}
