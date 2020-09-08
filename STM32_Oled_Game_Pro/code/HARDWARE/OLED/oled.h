#ifndef __OLED_H
#define __OLED_H	 
#include "sys.h"
/**********************************************�޸���************************************************/
//SCL PB6    SDA PB7
#define RCC_APB2Periph_OLED_SCL_PORT			RCC_APB2Periph_GPIOA			//RCC_APB2Periph_GPIOA~G
#define GPIO_OLED_SCL_PORT								GPIOA										//GPIOA~G
#define GPIO_Pin_OLED_SCL									GPIO_Pin_7							//GPIO_Pin_0~15

#define RCC_APB2Periph_OLED_SDA_PORT			RCC_APB2Periph_GPIOA				//RCC_APB2Periph_GPIOA~G
#define GPIO_OLED_SDA_PORT								GPIOA												//GPIOA~G
#define GPIO_Pin_OLED_SDA									GPIO_Pin_6							//GPIO_Pin_0~15


#define OLED_IIC_SCL											PAout(7)//SCL
#define OLED_IIC_SDA											PAout(6)//SDA
#define	OLED_READ_SDA											PAin(6)	//SDA״̬��ȡ
/*****************************************************************************************************/

#define OLED_ADDRESS	0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define SIZE 		16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

/////////////////////////////////////////////////////////////
//OLED_IICЭ�麯��///////////////////////////////////////////
void OLED_SDA_IN(void);
void OLED_SDA_OUT(void);
void OLED_IIC_Init(void);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_IIC_ACK(void);
void OLED_IIC_NACK(void);
unsigned char OLED_IIC_Wait_Ack(void);
void OLED_IIC_Write_Byte(unsigned char data);
void OLED_IIC_Write_Data(unsigned char Device_addr,unsigned char Reg_addr,unsigned char data);
unsigned char OLED_IIC_Read_Byte(unsigned char Ack_EN);
unsigned char OLED_IIC_Read_Data(unsigned char Device_addr,unsigned char Reg_addr,unsigned char ACK_EN);
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//OLED�����ú���///////////////////////////////////////////
void OLED_WriteCmd(unsigned char I2C_Command);						// -- д����
void OLED_WriteDat(unsigned char I2C_Data);							//-- д����
void OLED_Init(void);																//-- OLED����ʼ��
void OLED_SetPos(unsigned char x, unsigned char y);	//-- ������ʼ������
void OLED_Fill(unsigned char fill_Data);						//-- ȫ�����  0xff
void OLED_CLS(void);																//-- ����
void OLED_ON(void);																	//-- ����
void OLED_OFF(void);																//-- ˯��
void OLED_Refresh_Gram(void);														//-- ˢ��
/*-- ��ʾ�ַ���(�����С��6*8��8*16����)****/
//ֻ��ʾ�ַ�������ʾ����
/*-- ����OLED_ShowStr(0,0,"abc",2);*/
void OLED_ShowStr(unsigned char x,  char y,  char ch[], unsigned char TextSize);

/*-- ��ʾ����(������Ҫ��ȡģ��Ȼ��ŵ�codetab.h��*/
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

/*-- ��ʾ-- BMPͼƬ*/
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif

