/*
 * @Author: liubotao
 * @Date: 2022-11-05 16:40:34
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-07 02:16:19
 * @FilePath: \ds1302-lcd1602\USER\timer\timer.c
 * @Description: 
 * 
 */
#include "timer.h"

#define BCDTODEC(bcd) ((bcd) = (bcd-(bcd>>4)*6))
#define DECTOBCD(dec) ((dec) = (dec+(dec/10)*6))

unsigned char setTimer(TIMER_T *time,unsigned char modes,unsigned int num)
{
    time->setMode=modes;
    time->timeBuffer[modes]=num;
	return 0;
}
unsigned char modeIncident(TIMER_T *time)
{
    unsigned char timBuf[7]={0};
    unsigned char num;
    time->displayClear();
    time->rANDw= ~(time->rANDw);

    if (time->rANDw ==0 )
    {
        for (num = 0; num < 7; num++)
        {
            timBuf[num]=time->timeBuffer[num];
            
        }
        time->timerWrite(timBuf);  
    }
    else
    {
        time->timerRead(timBuf);
        for (num = 0; num < 7; num++)
        {
            time->timeBuffer[num]=timBuf[num];
            
        }
    }
    return 0;
}
unsigned char switchIncident(TIMER_T *time)
{
    time->displayClear();
    if (time->rANDw!=TIMSHOW)
    {
        time->setMode++;
        if (time->setMode > 5)
        {
            time->setMode=0;
        }
        
    }
	return 0;
}

unsigned char addIncident(TIMER_T *time)
{
    unsigned char num1;
    if (time->rANDw!=TIMSHOW)
    {
        num1=time->timeBuffer[time->setMode];
        BCDTODEC(num1);
        num1++;
        if(num1>60)num1=0;
        DECTOBCD(num1);
        time->timeBuffer[time->setMode]=num1;
        time->refreshClock(time);
    }
	time->displayClear();
	return 0;
}
unsigned char subIncident(TIMER_T *time)
{
    unsigned char num1;
    if (time->rANDw!=TIMSHOW)
    {
        num1=time->timeBuffer[time->setMode];
        BCDTODEC(num1);
        if(num1>0)num1--;
        DECTOBCD(num1);
        time->timeBuffer[time->setMode]=num1;
        time->refreshClock(time);
    }
	time->displayClear();
	return 0;
}

unsigned char showIncident(TIMER_T *time)
{
    if (time->rANDw==TIMSHOW)
    {

        time->refreshClock(time);
    }
    else
    {
        time->showClock(time);
    }
    if (time->rANDw == 0)
        time->displayWrite(12, 0, "Show");
    if (time->rANDw != 0)
    {
        time->displayWrite(12, 0, "Set");

        switch (time->setMode)
        {
        case second:
            time->displayWrite(11, 1, "second");
            break;
        case minute:
            time->displayWrite(11, 1, "minute");
            break;
        case hour:
            time->displayWrite(11, 1, "hour");
            break;
        case day:
            time->displayWrite(11, 1, "day");
            break;
        case month:
            time->displayWrite(11, 1, "month");
            break;
        case year:
            time->displayWrite(11, 1, "year");
            break;
        default:
            time->displayWrite(11, 1, "err");
            break;
        }
    }
	return 0;
}