/*** 
 * @Author: liubotao
 * @Date: 2022-11-01 09:53:41
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-01 10:13:18
 * @FilePath: \ds1302-lcd1602\BSP\Display\display.h
 * @Description: 
 * @
 */
#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#define PIN P2
#define PINS P3 

static void num4(unsigned int nums);
void setSeg(unsigned char num ,unsigned char bitNum);
void delay(unsigned int us);


#endif
