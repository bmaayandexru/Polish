#ifndef __TI_H__
#define	__TI_H__
#include "Defs.h"
#include "Timers.h"

// интервал TIMER1 MR0
// см. InitPlatform() в main.c
#define tickPeriod 5000
// период в микросекундах
#define timerPeriod (tickPeriod/100) 
// процедуры пересчета для модуля ti
#define tiSecToTick(x) 	((x)*(1000000/timerPeriod))
#define tiMsToTick(x) 	((x)*(1000/timerPeriod))
#define tiMksToTick(x) 	((x)/timerPeriod)
#define tiTickToMs(x)	(((x)*timerPeriod)/1000)
#define tiTickToMks(x) 	((x)*timerPeriod)

// старт интервала ni на tickcount интервалов таймера
#define StartTI(ni,tickcount) 	ti[ni]=tickcount+1
// оствновка интервала
#define StopTI(ni)				ti[ni]=1
// проверка интервала
#define EndTI(ni)				(ti[ni]==1)

// старт интервала ni 
#define StartTime(ni) 			time[ni] = 1
// оствновка интервала
#define StopTime(ni)			time[ni] = 0
// проверка интервала (размер)
#define GetTime(ni)				(time[ni]==0 ? 0:time[ni]-1)
// проверка пуска времени
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

// общий декремент таймеров. Располагается в обработчике таймера
//inline void DecTIs(void); 
//inline void IncTimes(void); 

extern volatile 	u32 	ti[];	// массив интервалов считаются декрементом
extern volatile	u32 	time[];	// массив времен считаются инкрементом
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
// интервал опроса Nextion
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
