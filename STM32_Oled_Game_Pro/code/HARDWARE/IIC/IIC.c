#include "iic.h"
/**********************************************/
//						IIC Start
//开始信号：在SCL为高电平时，SDA由高电平向低电平跳变，开始传输数据。
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
//结束信号：在SCL为高电平时，SDA由低电平向高电平跳变，结束传输数据。
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
//						IIC主机产生ACK应答信号
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
//						IIC主机不产生ACK应答信号
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
//等待应答信号到来
//返回值	1，接收应答失败
//        0，接收应答成功
/**********************************************/
unsigned char IIC_Wait_Ack(void)
{
    unsigned char ucErrTime = 0;
    SDA_IN(); //SDA设置为输入
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
    SCL_LOW(); //时钟输出0
    return 0;
}

/**********************************************/
// 						IIC Read byte
//IIC读一个字节	  
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
//**********************************************/
unsigned char IIC_Read_Byte(unsigned char Ack_EN)
{
    unsigned char i, receive = 0;
    SDA_IN(); //SDA设置为输入
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
        IIC_NACK(); //发送nACK
    else
        IIC_ACK(); //发送ACK
    return receive;
}

/**********************************************
// 						IIC Write byte
//IIC写一个字节	  
**********************************************/
void IIC_Write_Byte(unsigned char DATA)
{
    unsigned char i;
    SDA_OUT();
    SCL_LOW(); //拉低时钟开始数据传输
    for (i = 0; i < 8; i++)
    {
        IIC_SDA = (DATA & 0x80) >> 7;
        DATA = DATA << 1;
        //IIC_Delay_us(5); //对TEA5767芯片这三个延时都是必须的
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
    IIC_Write_Byte(Device_addr | 0x00); //器件地址(7位) + 读写位(写0)
    IIC_Wait_Ack();
    IIC_Write_Byte(Reg_addr); 					//要读数据的寄存器地址
    IIC_Wait_Ack();
    IIC_Start();
    SDA_IN();
    IIC_Write_Byte(Device_addr | 0x01); //器件地址(7位) + 读写位(读1)
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
    IIC_Write_Byte(Device_addr | 0x00); //器件地址(7位) + 读写位(读1写0)
    IIC_Wait_Ack();
    IIC_Write_Byte(Reg_addr); //要写入数据的寄存器地址
    IIC_Wait_Ack();
    IIC_Write_Byte(DATA);
    IIC_Wait_Ack();
    IIC_Stop();
}
