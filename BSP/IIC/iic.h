#ifndef __IIC_H_
#define __IIC_H_

#include <reg51.h>

#define uint8_t unsigned char
#define uint16_t unsigned int


sbit SDA = P1^0;
sbit SCL = P1^1;

void iicStart(void); 
void iicStop(void);  
uint8_t iicWaitAck(void);  
void iicSendAck(uint8_t ackbit); 
void iicSendByte(uint8_t byt); 
uint8_t iicRecByte();



 
#endif