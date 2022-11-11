/*
 * @Author: liubotao
 * @Date: 2022-10-31 10:10:49
 * @LastEditors: liubotao
 * @LastEditTime: 2022-10-31 15:56:28
 * @FilePath: \ds1302-lcd1602\BSP\IIC\iic.c
 * @Description: iic 低位先
 * 
 */
#include "iic.h"
#include <intrins.h>
#define DELAY_TIME 5


void iicDelay(uint8_t i)
{
    do{_nop_();}
    while(i--);        
}

//I2C总线启动信号
void iicStart(void)
{
    SDA = 1;
    SCL = 1;
    _nop_();
    SDA = 0;
    _nop_();
    SCL = 0;	
}

//I2C总线停止信号
void iicStop(void)
{
    SDA = 0;
    SCL = 1;
    _nop_();
    SDA = 1;
    _nop_();
}

//发送应答或非应答信号
void iicSendAck(uint8_t ackbit)
{
    SCL = 0;
    SDA = ackbit;  					
    _nop_();
    SCL = 1;
    _nop_();
    SCL = 0; 
    SDA = 1;
    _nop_();
}

//等待应答
uint8_t iicWaitAck(void)
{
    uint8_t ackbit;
	
    SCL  = 1;
    _nop_();
    ackbit = SDA;
    SCL = 0;
    _nop_();
    return ackbit;
}

//I2C总线发送一个字节数据
void iicSendByte(uint8_t byt)
{
    uint8_t i;

    for(i=0; i<8; i++)
    {
        SDA = byt & 0x01; 
        byt >>= 1;
        SCL = 1; 
        _nop_();
        SCL = 0;
        _nop_();
    }
   // SCL  = 0;  
}

//I2C总线接收一个字节数据
uint8_t iicRecByte()
{
    uint8_t n,dat,dat1;

	for(n=0; n<8; n++)
	{
		dat1 = SDA;
		dat = (dat>>1) | (dat1<<7);
		SCL = 1;
		_nop_();
		SCL = 0;
		_nop_();
	}
    return dat;    
}






