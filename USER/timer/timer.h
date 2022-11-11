/*** 
 * @Author: liubotao
 * @Date: 2022-11-05 16:40:34
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-07 02:18:11
 * @FilePath: \ds1302-lcd1602\USER\timer\timer.h
 * @Description: 
 * @
 */
#ifndef _TIMER_H
#define _TIMER_H

//#include "type.h"
//struct TIMER_T;
#define TIMSHOW 0
//#define TIMSET  1

typedef struct Timer TIMER_T;

struct Timer
{
	unsigned char  rANDw;	    //设置还是显示
    unsigned char  setMode;   //设置模式
    		
    unsigned char  timeBuffer[8]; //储存时间

    unsigned char (*setClock)(TIMER_T * t);     //设置芯片
    unsigned char (*showClock)(TIMER_T * t);    //显示时间
    unsigned char (*refreshClock)(TIMER_T * t);    //显示时间
    unsigned char (*timerRead) (unsigned char *buf);//读数据
    unsigned char (*timerWrite) (unsigned char *buf);//写数据
    unsigned char (*displayClear)(void);    //清屏
    unsigned char (*displayWrite) (unsigned char x,unsigned char y,unsigned char *buf);//屏幕写数据

};


typedef enum
{
    
    second,
    minute,
    hour,
    day,
    month,
    year,
}TIMER_ENUM;


unsigned char setTimer(TIMER_T *time,unsigned char a,unsigned short int b);//设置时间
unsigned char addIncident(TIMER_T *time);           //加 按键事件
unsigned char subIncident(TIMER_T *time);           //减 按键事件
unsigned char showIncident(TIMER_T *time);          //显示事件
unsigned char switchIncident(TIMER_T *time);        //切换设置
unsigned char modeIncident(TIMER_T *time);          //显示模式选择

#endif
