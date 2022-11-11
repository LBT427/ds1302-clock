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
	unsigned char  rANDw;	    //���û�����ʾ
    unsigned char  setMode;   //����ģʽ
    		
    unsigned char  timeBuffer[8]; //����ʱ��

    unsigned char (*setClock)(TIMER_T * t);     //����оƬ
    unsigned char (*showClock)(TIMER_T * t);    //��ʾʱ��
    unsigned char (*refreshClock)(TIMER_T * t);    //��ʾʱ��
    unsigned char (*timerRead) (unsigned char *buf);//������
    unsigned char (*timerWrite) (unsigned char *buf);//д����
    unsigned char (*displayClear)(void);    //����
    unsigned char (*displayWrite) (unsigned char x,unsigned char y,unsigned char *buf);//��Ļд����

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


unsigned char setTimer(TIMER_T *time,unsigned char a,unsigned short int b);//����ʱ��
unsigned char addIncident(TIMER_T *time);           //�� �����¼�
unsigned char subIncident(TIMER_T *time);           //�� �����¼�
unsigned char showIncident(TIMER_T *time);          //��ʾ�¼�
unsigned char switchIncident(TIMER_T *time);        //�л�����
unsigned char modeIncident(TIMER_T *time);          //��ʾģʽѡ��

#endif
