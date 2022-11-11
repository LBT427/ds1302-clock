/*** 
 * @Author: liubotao
 * @Date: 2022-10-30 15:02:44
 * @LastEditors: liubotao
 * @LastEditTime: 2022-10-31 10:14:38
 * @FilePath: \ds1302-lcd1602\BSP\LCD\lcd1602.h
 * @Description: 
 * @
 */
#ifndef __LCD1602_H_
#define __LCD1602_H_

#include <reg51.h>

#define uint8_t unsigned char
#define uint16_t unsigned int


#define LCD1602_DB  P0      
sbit LCD1602_RS = P2^0;
sbit LCD1602_RW = P2^1;
sbit LCD1602_EN = P2^2;	 


void readBusy();                                                  //Ã¦¼ì²â
void lcd1602WriteCmd(uint8_t cmd);                                //Ð´ÃüÁî
void lcd1602WriteData(uint8_t dat);                               //Ð´Êý¾Ý
void lcdSetCursor(uint8_t x,uint8_t y);                    		  //×ø±êÉèÖÃ
uint8_t LcdShowStr(uint8_t x,uint8_t y,uint8_t *str);    			  //ÏÔÊ¾×Ö·û´®
uint8_t initLcd1602();                                               //1602³õÊ¼»¯
					  

#endif
