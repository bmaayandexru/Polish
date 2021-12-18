#ifndef __TI_H__
#define	__TI_H__
#include "Defs.h"
#include "Timers.h"

// �������� TIMER1 MR0
// ��. InitPlatform() � main.c
#define tickPeriod 5000
// ������ � �������������
#define timerPeriod (tickPeriod/100) 
// ��������� ��������� ��� ������ ti
#define tiSecToTick(x) 	((x)*(1000000/timerPeriod))
#define tiMsToTick(x) 	((x)*(1000/timerPeriod))
#define tiMksToTick(x) 	((x)/timerPeriod)
#define tiTickToMs(x)	(((x)*timerPeriod)/1000)
#define tiTickToMks(x) 	((x)*timerPeriod)

// ����� ��������� ni �� tickcount ���������� �������
#define StartTI(ni,tickcount) 	ti[ni]=tickcount+1
// ��������� ���������
#define StopTI(ni)				ti[ni]=1
// �������� ���������
#define EndTI(ni)				(ti[ni]==1)

// ����� ��������� ni 
#define StartTime(ni) 			time[ni] = 1
// ��������� ���������
#define StopTime(ni)			time[ni] = 0
// �������� ��������� (������)
#define GetTime(ni)				(time[ni]==0 ? 0:time[ni]-1)
// �������� ����� �������
#define StartedTime(ni) 			(time[ni] > 0)


#define TITimer(Name,Interval,Code,ElseCode) if(EndTI(Name)) \
	{ \
		if (Interval) { \
		{ Code;  StartTI(Name,Interval); } 	\
		} \
	} else { \
		ElseCode; \
	}

#define StartTimeTC(t) t=LPC_TIM0->TC
#define ShowTimeTC(t,n) if(t)\
	{\
		if (t < LPC_TIM0->TC) t=LPC_TIM0->TC-t;\
		else t=0xFFFFFFFF+LPC_TIM0->TC-t;\
		Msg("tc%d: %d\r\n",n,t);\
		t=0;\
	}

// ����� ��������� ��������. ������������� � ����������� �������
//inline void DecTIs(void); 
//inline void IncTimes(void); 

extern volatile 	u32 	ti[];	// ������ ���������� ��������� �����������
extern volatile	u32 	time[];	// ������ ������ ��������� �����������
extern TIMER_CONTROL_STRUCT tcs_TI;
extern u32 T1,T2,T3;

void TI_Handler(void);

#define tiTx485Delay 0

#define tiTest 						1
#define tiQTest 					2
#define tiLensSmdWait 		3
#define tiOutAT 					4
#define tiPrgExe 					5
#define tiPrgPause 				6
#define tiCtrlBlk 				7
#define tiMBWait 					8
#define tiQueue 					9
#define tiTest2 					10
#define tiFQGetPult 			11
//#define tiFQGetLS	12
#define tiFQGetPress 			13
#define tiFQTest 					14
#define tiTestTime				15
#define tiPrgExeNonStop 	16
#define tiRecBlock 				17
#define tiRetrySendPoint	18
// �������� ������ Nextion
#define tiNextSendme			19


#define timeWaitUART0 0
#define timeWaitUART1 1
#define timeTest			2

#ifdef __FREZER__
#define timeXdir	3
#define timeXback	4
#define timeYdir	5
#define timeYback	6
#define timeZdir	7
#define timeZback	8
#endif

#define timeIN1		11	
#define timeIN2		12
#define timeIN3		13
#define timeIN4		14
#define timeIN5		16
#define timeIN6		17
#define timeIN7		18
#define timeIN8		19
#define timeIN9		20
#define timeIN10	21
#define timeIN11	22
#define timeIN12	23
#define timeIN13	24
#define timeIN14	25
#define timeIN15	26
#define timeIN16	27
#define timeSTH		28
#define timeTrCalc		29

#endif
