/*
 * @Author: liubotao
 * @Date: 2019-04-10 10:17:14
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-06 10:45:52
 * @FilePath: \ds1302-lcd1602\BSP\DS1302\ds1302.c
 * @Description: 
 * 
 */
#include <intrins.h>
#include "ds1302.h"
#include "iic.h"

//秒分时日月周年
uint8_t code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
uint8_t code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//秒分时日月周年

void ds1302Write(uint8_t addr, uint8_t *dat)
{
//	uint8_t n;
	RST = 0;
	_nop_();

	SCLK = 0;
	_nop_();
	RST = 1; 
	_nop_();
	iicSendByte(addr);
	iicSendByte(*dat);
 
	RST = 0;
	_nop_();
}

uint8_t ds1302Read(uint8_t addr,uint8_t *dat)
{
	RST = 0;
	_nop_();
	SCLK = 0;
	_nop_();
	RST = 1;
	_nop_();
	iicSendByte(addr);

	_nop_();
	*dat=iicRecByte();

	RST = 0;
	_nop_();	
	SCLK = 1;
	_nop_();
	DSIO = 0;
	_nop_();
	DSIO = 1;
	_nop_();
	return dat;	
}

uint8_t ds1302Init(uint8_t *bufer)
{
	uint8_t n;
	ds1302Write(0x8E,0X00);
	for (n=0; n<7; n++)
	{
		ds1302Write(WRITE_RTC_ADDR[n],&bufer[n]);	
	}
	ds1302Write(0x8E,0x80);
	return 0;
}

void ds1302ReadTime(uint8_t *buf)
{
	uint8_t n;
	for (n=0; n<7; n++)
	{
		 ds1302Read(READ_RTC_ADDR[n],&buf[n]);
	}
		
}
void dataPros(uint8_t *buf_s,uint8_t *buf_d)
{
	uint8_t datas[8];
   	ds1302ReadTime(datas);
	buf_s[0] = (datas[2]/16)+0x30;				//时
	buf_s[1] = (datas[2]&0x0f)+0x30;				 
	buf_s[2] = '-';
	buf_s[3] = (datas[1]/16)+0x30;				//分
	buf_s[4] = (datas[1]&0x0f)+0x30;	
	buf_s[5] = '-';
	buf_s[6] = (datas[0]/16)+0x30;				//秒
	buf_s[7] = (datas[0]&0x0f)+0x30;

	buf_d[0] = (datas[6] / 16) + 0x30; //日
	buf_d[1] = (datas[6] & 0x0f) + 0x30;
	buf_d[2] = '-';
	buf_d[3] = (datas[4] / 16) + 0x30; //月
	buf_d[4] = (datas[4] & 0x0f) + 0x30;
	buf_d[5] = '-';
	buf_d[6] = (datas[3] / 16) + 0x30; //年
	buf_d[7] = (datas[3] & 0x0f) + 0x30;

}

