/*** 
 * @Author: liubotao
 * @Date: 2019-04-10 10:17:14
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-06 10:46:12
 * @FilePath: \ds1302-lcd1602\BSP\DS1302\ds1302.h
 * @Description: 
 * @
 */
#ifndef __DS1302_H_
#define __DS1302_H_

#include <reg51.h>

#define uint8_t unsigned char
#define uint16_t unsigned int


sbit DSIO=P1^0;
sbit RST=P1^2;
sbit SCLK=P1^1;

void ds1302Write(uint8_t addr, uint8_t *dat);
uint8_t ds1302Read(uint8_t addr,uint8_t *dat);
uint8_t ds1302Init(uint8_t *bufer);
void ds1302ReadTime(uint8_t *buf);
void dataPros(uint8_t *buf_s,uint8_t *buf_d);

#endif