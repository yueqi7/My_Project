#include "iic.h"
/**********************************************/
//						IIC Start
//��ʼ�źţ���SCLΪ�ߵ�ƽʱ��SDA�ɸߵ�ƽ��͵�ƽ���䣬��ʼ�������ݡ�
/**********************************************/
void IIC_Start()
{
    SDA_OUT();
    SDA_HIGH();
    SCL_HIGH();
    //IIC_Delay_us(2);
    SDA_LOW();
    //IIC_Delay_us(2);
    SCL_LOW();
}

/**********************************************/
//						IIC Stop
//�����źţ���SCLΪ�ߵ�ƽʱ��SDA�ɵ͵�ƽ��ߵ�ƽ���䣬�����������ݡ�
/**********************************************/
void IIC_Stop()
{
    SDA_OUT();
    SCL_LOW();
    SDA_LOW();
    //IIC_Delay_us(2);
    SCL_HIGH();
    SDA_HIGH();
    //IIC_Delay_us(2);
}

/**********************************************/
//						IIC��������ACKӦ���ź�
/**********************************************/
void IIC_ACK(void)
{
	SCL_LOW();
	SDA_OUT();
	SDA_LOW();
	//IIC_Delay_us(2);
	SCL_HIGH();
	//IIC_Delay_us(2);
	SCL_LOW();
}

/**********************************************/
//						IIC����������ACKӦ���ź�
/**********************************************/
void IIC_NACK(void)

{
    SCL_LOW();
    SDA_OUT();
    SDA_HIGH();
    //IIC_Delay_us(2);
    SCL_HIGH();
    //IIC_Delay_us(2);
    SCL_LOW();
}

/**********************************************/
//						IIC Wait Ack
//�ȴ�Ӧ���źŵ���
//����ֵ	1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
/**********************************************/
unsigned char IIC_Wait_Ack(void)
{
    unsigned char ucErrTime = 0;
    SDA_IN(); //SDA����Ϊ����
    SDA_HIGH();    
		//IIC_Delay_us(2);
    SCL_HIGH(); 
		//IIC_Delay_us(2);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    SCL_LOW(); //ʱ�����0
    return 0;
}

/**********************************************/
// 						IIC Read byte
//IIC��һ���ֽ�	  
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
//**********************************************/
unsigned char IIC_Read_Byte(unsigned char Ack_EN)
{
    unsigned char i, receive = 0;
    SDA_IN(); //SDA����Ϊ����
    for (i = 0; i < 8; i++)
    {
        SCL_LOW();
        //IIC_Delay_us(2);
        SCL_HIGH();
        receive <<= 1;
        if (READ_SDA)
            receive++;
    //IIC_Delay_us(2);
    }
    if (!Ack_EN)
        IIC_NACK(); //����nACK
    else
        IIC_ACK(); //����ACK
    return receive;
}

/**********************************************
// 						IIC Write byte
//IICдһ���ֽ�	  
**********************************************/
void IIC_Write_Byte(unsigned char DATA)
{
    unsigned char i;
    SDA_OUT();
    SCL_LOW(); //����ʱ�ӿ�ʼ���ݴ���
    for (i = 0; i < 8; i++)
    {
        IIC_SDA = (DATA & 0x80) >> 7;
        DATA = DATA << 1;
        //IIC_Delay_us(5); //��TEA5767оƬ��������ʱ���Ǳ����
        SCL_HIGH();
        //IIC_Delay_us(5);
        SCL_LOW();
        //IIC_Delay_us(5);
    }
}

/**********************************************
// IIC Read Data
**********************************************/
unsigned char IIC_Read_Data(unsigned char Device_addr, unsigned char Reg_addr, unsigned char ACK_EN)
{
    unsigned char receive;
    IIC_Start();
    IIC_Write_Byte(Device_addr | 0x00); //������ַ(7λ) + ��дλ(д0)
    IIC_Wait_Ack();
    IIC_Write_Byte(Reg_addr); 					//Ҫ�����ݵļĴ�����ַ
    IIC_Wait_Ack();
    IIC_Start();
    SDA_IN();
    IIC_Write_Byte(Device_addr | 0x01); //������ַ(7λ) + ��дλ(��1)
    IIC_Wait_Ack();
    receive = IIC_Read_Byte(ACK_EN);
    IIC_Wait_Ack();
    IIC_Stop();
    return receive;
}

/**********************************************
// IIC Write Data
**********************************************/
void IIC_Write_Data(unsigned char Device_addr, unsigned char Reg_addr, unsigned char DATA)
{
    IIC_Start();
    SDA_OUT();
    IIC_Write_Byte(Device_addr | 0x00); //������ַ(7λ) + ��дλ(��1д0)
    IIC_Wait_Ack();
    IIC_Write_Byte(Reg_addr); //Ҫд�����ݵļĴ�����ַ
    IIC_Wait_Ack();
    IIC_Write_Byte(DATA);
    IIC_Wait_Ack();
    IIC_Stop();
}
