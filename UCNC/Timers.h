#ifndef __TIMERS_H__
#define __TIMERS_H__

//#include <RTL.h>
#include "Defs.h"

// ������ ����� �������� TC � �� (������������) ��� ���� ��������
#define tmPeriod (100) 
// ��������� ��������� ��� ������ Timers
#define tmSecToTick(x) 	(x*(1000000*1000/tmPeriod))
#define tmMsToTick(x) 	(x*(1000*1000/tmPeriod))
#define tmMksToTick(x) 	(x*1000/tmPeriod)
#define tmTickToMs(x)	((x*tmPeriod)/1000000)
#define tmTickToMks(x) 	((x*tmPeriod)/1000)

#define TCS_SetInterval(cs,i) 	cs.interval = i

// ������� !!!!
//#define TCS_SetInterval(cs,i) 	{cs.interval = i; if ((i<5000)&&(i > 2500000)) Msg("i %d\r\n",i);}
#define TCS_Start(cs) 			{if (!cs.enabled) {*(cs.pMR) = *(cs.pTC) + 2500000; cs.enabled = TRUE;}}
#define TCS_Stop(cs) 			cs.enabled = FALSE
#define TCS_Started(cs) 		(cs.enabled)

typedef void(*TTimerHandler)(void);

typedef struct
{
  volatile 	BOOL 	enabled; 
  volatile 	u32 	interval;   	// � ����� ������� (0,04 ���)
	volatile	u32*	pMR;
	volatile 	u32*	pTC;	
	TTimerHandler 	handler;		// ����� �����������
	// ������� ���������� ����������
  volatile 	u32 	dtfix;   		
  volatile 	u32 	intfix;   	
} TIMER_CONTROL_STRUCT;

// ������������
extern volatile u32 T1T0p,U1T0p,U0T0p;
// �������� ��� ������� �������� ����� ������
// ������������ � main.c
extern volatile TIMER_CONTROL_STRUCT *T0MR0,*T0MR1,*T0MR2,*T0MR3;
extern volatile TIMER_CONTROL_STRUCT *T1MR0,*T1MR1,*T1MR2,*T1MR3;
extern volatile TIMER_CONTROL_STRUCT *T2MR0,*T2MR1,*T2MR2,*T2MR3;
extern volatile TIMER_CONTROL_STRUCT *T3MR0,*T3MR1,*T3MR2,*T3MR3;

void Init_TCS(volatile TIMER_CONTROL_STRUCT* CTS,u8 t,u8 mr,TTimerHandler h);


void InitTimer(u8 num);
void InitTimer1(u8 num);

//void InitTimer0(u32 pv,u32 mv);

#endif
