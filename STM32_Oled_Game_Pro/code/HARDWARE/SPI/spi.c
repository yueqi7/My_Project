#include "spi.h"


void MySPI_Init(void)
{
	SPI_InitTypeDef  SPI_Init_config;
	GPIO_InitTypeDef 	GPIO_InitStructure;
	
	RCC_SPI; 
	RCC_APB2PeriphClockCmd(	RCC_GPIO, ENABLE );//PORTBʱ��ʹ�� 
	GPIO_InitStructure.GPIO_Pin = SPI_SCLK_IO|SPI_MISO_IO|SPI_MOSI_IO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIOB
 	GPIO_SetBits(SPI_GPIO_PORT,SPI_SCLK_IO|SPI_MISO_IO|SPI_MOSI_IO);  //PB13/14/15����

	SPI_Init_config.SPI_Direction		= SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_Init_config.SPI_Mode 				= SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_Init_config.SPI_DataSize		= SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_Init_config.SPI_CPOL 				= SPI_CPOL_Low;		//ѡ���˴���ʱ�ӵ���̬:����ʱ�ӵ�
	SPI_Init_config.SPI_CPHA 				= SPI_CPHA_1Edge;	//���ݲ���(����)�ڵ�1��ʱ����
	SPI_Init_config.SPI_NSS					= SPI_NSS_Soft;//SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_Init_config.SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_Init_config.SPI_FirstBit 			= SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_Init_config.SPI_CRCPolynomial 		= 7;	//CRCֵ����Ķ���ʽ
	
	SPI_Init(MYSPI, &SPI_Init_config);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(MYSPI, ENABLE); //ʹ��SPI����
} 


uint8_t SPI_ReadWriteByte(uint8_t spi_byte)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(MYSPI, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(MYSPI, spi_byte); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(MYSPI, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(MYSPI); //����ͨ��SPIx������յ�����			
}
