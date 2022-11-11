/*
 * @Author: liubotao
 * @Date: 2022-10-30 15:02:33
 * @LastEditors: liubotao
 * @LastEditTime: 2022-10-31 10:13:44
 * @FilePath: \ds1302-lcd1602\BSP\LCD\lcd1602.c
 * @Description: 
 * 
 */
#include "lcd1602.h"

void readBusy()           
{
    uint8_t sta;      
    LCD1602_DB = 0xff;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        sta = LCD1602_DB;
        LCD1602_EN = 0;    
    }while(sta & 0x80);
}

void lcd1602WriteCmd(uint8_t cmd)     
{
    readBusy();
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DB = cmd;
    LCD1602_EN = 1;
    LCD1602_EN = 0;    
}

void lcd1602WriteData(uint8_t dat)   
{
      readBusy();
      LCD1602_RS = 1;
      LCD1602_RW = 0;
      LCD1602_DB = dat;
      LCD1602_EN = 1;
      LCD1602_EN = 0;
}

void lcdSetCursor(uint8_t x,uint8_t y)  
{
    uint8_t addr;
    if(y == 0)
        addr = 0x00 + x;
    else
        addr = 0x40 + x;
    
    lcd1602WriteCmd(addr|0x80);
}

uint8_t LcdShowStr(uint8_t x,uint8_t y,uint8_t *str)     
{
    lcdSetCursor(x,y);      
    while(*str != '\0')
    {
        lcd1602WriteData(*str++);
    }
	return 0;
}

uint8_t initLcd1602()              
{
    lcd1602WriteCmd(0x38);    
    lcd1602WriteCmd(0x0c);
    lcd1602WriteCmd(0x06);
    lcd1602WriteCmd(0x01); 
	return 0;	
}