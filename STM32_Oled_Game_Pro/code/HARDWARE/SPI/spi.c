#include "spi.h"


void MySPI_Init(void)
{
	SPI_InitTypeDef  SPI_Init_config;
	GPIO_InitTypeDef 	GPIO_InitStructure;
	
	RCC_SPI; 
	RCC_APB2PeriphClockCmd(	RCC_GPIO, ENABLE );//PORTB时钟使能 
	GPIO_InitStructure.GPIO_Pin = SPI_SCLK_IO|SPI_MISO_IO|SPI_MOSI_IO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitStructure);//初始化GPIOB
 	GPIO_SetBits(SPI_GPIO_PORT,SPI_SCLK_IO|SPI_MISO_IO|SPI_MOSI_IO);  //PB13/14/15上拉

	SPI_Init_config.SPI_Direction		= SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_Init_config.SPI_Mode 				= SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_Init_config.SPI_DataSize		= SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_Init_config.SPI_CPOL 				= SPI_CPOL_Low;		//选择了串行时钟的稳态:空闲时钟低
	SPI_Init_config.SPI_CPHA 				= SPI_CPHA_1Edge;	//数据捕获(采样)于第1个时钟沿
	SPI_Init_config.SPI_NSS					= SPI_NSS_Soft;//SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_Init_config.SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_Init_config.SPI_FirstBit 			= SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_Init_config.SPI_CRCPolynomial 		= 7;	//CRC值计算的多项式
	
	SPI_Init(MYSPI, &SPI_Init_config);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	SPI_Cmd(MYSPI, ENABLE); //使能SPI外设
} 


uint8_t SPI_ReadWriteByte(uint8_t spi_byte)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(MYSPI, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(MYSPI, spi_byte); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(MYSPI, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(MYSPI); //返回通过SPIx最近接收的数据			
}
