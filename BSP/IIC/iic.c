/*
 * @Author: liubotao
 * @Date: 2022-10-31 10:10:49
 * @LastEditors: liubotao
 * @LastEditTime: 2022-10-31 15:56:28
 * @FilePath: \ds1302-lcd1602\BSP\IIC\iic.c
 * @Description: iic ��λ��
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

//I2C���������ź�
void iicStart(void)
{
    SDA = 1;
    SCL = 1;
    _nop_();
    SDA = 0;
    _nop_();
    SCL = 0;	
}

//I2C����ֹͣ�ź�
void iicStop(void)
{
    SDA = 0;
    SCL = 1;
    _nop_();
    SDA = 1;
    _nop_();
}

//����Ӧ����Ӧ���ź�
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

//�ȴ�Ӧ��
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

//I2C���߷���һ���ֽ�����
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

//I2C���߽���һ���ֽ�����
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






