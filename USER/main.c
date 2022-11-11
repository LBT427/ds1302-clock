/*
 * @Author: liubotao
 * @Date: 2022-10-26 10:24:52
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-07 02:19:11
 * @FilePath: \ds1302-lcd1602\USER\main.c
 * @Description: 
 * 
 */
#include <reg51.h>
#include "lcd1602.h"
#include "ds1302.h"
#include "timer.h"


sbit k1=P3^0;
sbit k2=P3^1;
sbit k3=P3^2;
sbit k4=P3^3;


void timer0Init();
void task100ms();

unsigned  char mainSetClock(TIMER_T * t);
unsigned  char mainShowClock(TIMER_T * t);//显示正在设置的时间
unsigned  char mainRefreshClock(TIMER_T * t);//显示时钟芯片的时间


TIMER_T  timer=
{
	0,
	0,
	{0, 0x30, 0x16, 0x31, 0x10, 0x06, 0x22},
	mainSetClock,
	mainShowClock,
	mainRefreshClock,
	ds1302ReadTime,
	ds1302Init,
	initLcd1602,
	LcdShowStr,
};

//uint8_t code TIME[7] = {0, 0x30, 0x16, 0x31, 0x10, 0x06, 0x22};


void main()
{ 	
 	initLcd1602();
	//ds1302Init(timer.timeBuffer);
	timer.setClock(&timer);
	timer0Init();
	while(1)
	{
		showIncident(&timer);
	}
}

unsigned  char mainSetClock(TIMER_T * t)
{

	ds1302Init(t->timeBuffer);
}

unsigned  char mainShowClock(TIMER_T * t)//显示正在设置的时间
{

	unsigned  char buf_s[9]={0};
	unsigned  char buf_d[13]={0};

	buf_s[0] = (t->timeBuffer[2]/16)+0x30;				
	buf_s[1] = (t->timeBuffer[2]&0x0f)+0x30;				 
	buf_s[2] = '-';
	buf_s[3] = (t->timeBuffer[1]/16)+0x30;				
	buf_s[4] = (t->timeBuffer[1]&0x0f)+0x30;	
	buf_s[5] = '-';
	buf_s[6] = (t->timeBuffer[0]/16)+0x30;				
	buf_s[7] = (t->timeBuffer[0]&0x0f)+0x30;

	buf_d[0] = (t->timeBuffer[6] / 16) + 0x30; 
	buf_d[1] = (t->timeBuffer[6] & 0x0f) + 0x30;
	buf_d[2] = '-';
	buf_d[3] = (t->timeBuffer[4] / 16) + 0x30; 
	buf_d[4] = (t->timeBuffer[4] & 0x0f) + 0x30;
	buf_d[5] = '-';
	buf_d[6] = (t->timeBuffer[3] / 16) + 0x30; 
	buf_d[7] = (t->timeBuffer[3] & 0x0f) + 0x30;
	LcdShowStr(0,0,buf_s); 
	LcdShowStr(0,1,buf_d); 
	
}

unsigned char mainRefreshClock(TIMER_T * t)//显示时钟芯片的时间
{
	unsigned  char buffer_1[9]={0};
	unsigned  char buffer_2[13]={0};
	
	dataPros(buffer_1,buffer_2);

	LcdShowStr(0,0,buffer_1); 
	LcdShowStr(0,1,buffer_2);
}


void timer0Init()
{
	TMOD |= 0X10;

	TH1 = 0XFC; //定时1ms
	TL1 = 0X18;
	ET1 = 1;
	EA = 1;
	TR1 = 1;
}

void Timer1() interrupt 3
{
	static int time_num;
	TH1 = 0XFC; //定时1ms
	TL1 = 0X18;
	time_num++;
	if (time_num == 20)//20ms
	{
		time_num = 0;
		task100ms();
	}
}


void task100ms()
{
	static int task_k1num=0,task_k2num=0,task_k3num=0,task_k4num=0;
	static unsigned char k1Val=0,k2Val=0,k3Val=0,k4Val=0;
	if(k1==0)
	{
		task_k1num++;
		if (task_k1num>3)//60ms
		{
			if (k1Val==0)//60ms
			{
				modeIncident(&timer);
				task_k1num=0;	
				k1Val=1;//标志位置1，代表按下没有松开
			}
		}
	}
	else if(k1==1)
	{
		task_k1num=0;	
		k1Val=0;//标志位置0，代表按下松开了，或者没有按下。
	}

	if(k2==0)
	{
		task_k2num++;
		if (task_k2num>3)//60ms
		{
			if (k2Val==0)//60ms
			{
				addIncident(&timer);
				task_k2num=0;	
				k2Val=1;//标志位置1，代表按下没有松开
			}
		}
	}
	else if(k2==1)
	{
		task_k2num=0;	
		k2Val=0;//标志位置0，代表按下松开了，或者没有按下。
	}

	if(k3==0)
	{
		task_k3num++;
		if (task_k3num>3)//60ms
		{
			if (k3Val==0)//60ms
			{
				subIncident(&timer);
				task_k3num=0;	
				k3Val=1;//标志位置1，代表按下没有松开
			}
		}
	}
	else if(k3==1)
	{
		task_k3num=0;	
		k3Val=0;//标志位置0，代表按下松开了，或者没有按下。
	}

	if(k4==0)
	{
		task_k4num++;
		if (task_k4num>3)//60ms
		{
			if (k4Val==0)//60ms
			{
				switchIncident(&timer);
				task_k4num=0;	
				k4Val=1;//标志位置1，代表按下没有松开
			}
		}
	}
	else if(k4==1)
	{
		task_k4num=0;	
		k4Val=0;//标志位置0，代表按下松开了，或者没有按下。
	}

	
}