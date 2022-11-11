/*
 * @Author: liubotao
 * @Date: 2022-11-01 09:53:31
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-01 10:11:49
 * @FilePath: \ds1302-lcd1602\BSP\Display\display.c
 * @Description: 
 * 
 */
#include "display.h"
#include <reg51.h>



unsigned char numS[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};


void delay(unsigned int us)
{
 while(us--); 
}

void setSeg(unsigned char num ,unsigned char bitNum)
{
 if(bitNum>8)return;
 if(num>9)return;

 PINS=numS[num];
 switch(bitNum)
 {
  case 1: PIN=0x01;break;
  case 2: PIN=0x02;break;  
  case 3: PIN=0x04;break; 
  case 4: PIN=0x08;break; 
  case 5: PIN=0x10;break;
  case 6: PIN=0x20;break;  
  case 7: PIN=0x40;break; 
  case 8: PIN=0x80;break; 

 }
 delay(100);
 PIN=0x00;
}


void num4(unsigned int nums)
{
 setSeg((nums/1000)%10,1);
 setSeg((nums/100)%10,2);
 setSeg((nums/10)%10,3);
 setSeg(nums%10,4);
}



// void main()
// { 
//  while(1)
//  {
//   num4(1357);

//  }
// }