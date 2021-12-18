#include "Defs.h"
#include "lpc17xx_timer.h"
#include "Timers.h"
#include "msg.h"
#include "ti.h"

volatile TIMER_CONTROL_STRUCT *T0MR0=0,*T0MR1=0,*T0MR2=0,*T0MR3=0;
volatile TIMER_CONTROL_STRUCT *T1MR0=0,*T1MR1=0,*T1MR2=0,*T1MR3=0;
volatile TIMER_CONTROL_STRUCT *T2MR0=0,*T2MR1=0,*T2MR2=0,*T2MR3=0;
volatile TIMER_CONTROL_STRUCT *T3MR0=0,*T3MR1=0,*T3MR2=0,*T3MR3=0;
/*
typedef struct
{
  volatile 	BOOL 	enabled; 
  volatile 	u32 	interval;   	// в тиках таймера (0,04 мкс)
	volatile	u32*	pMR;
	volatile 	u32*	pTC;	
	TTimerHandler 	handler;		// адрес обработчика
	// отладка перехлеста прерываний
  volatile 	u32 	dtfix;   		
  volatile 	u32 	intfix;   	
} TIMER_CONTROL_STRUCT;
// РАСПИСАТЬ АЛГОРИТМ РАСЧЕТА СЛЕДУЮЩЕГО ИНТЕРВАЛА
// ДЛЯ ЭТОГО И ВЫНЕСЕНА СТРУКТУРА
// 	Расчет MR выполняется после выхода из обработчика
NEXT_INT(LPC_TIM0,MR0,T0MR0,35,15);
регистр TC считает от до FFFFFFFF циклично
прерыванние срабатывает когда MR==TC
после обработки прерывания TC просчитывает какое-то значение т е MR!=TC
расчитывается значение dt для определения уместится ли следующий интервал в прямой счет
по сути dt это количество тиков прошедших за вызов обработчика
если dt+i1 < интервала то MR+=интервал - стандартная хорошая ситуация
иначе нужно как можно быстрее организовать вызов обработчика
т е MR=TC+i2 идет не инкремент MR на интервал а к TC прибавляем i2 (не большое число) 
чтоб прерывание произошло как можно раньше
экспериментально i1 установлено как 35(циклов) а i2 как 15 циклов
dtfix и intfix заведены для отладки алгоритма и больше в принципе не нужны

*/
#define NEXT_INT(tmr,mr,ts,i1,i2) { \
				if (tmr->mr < tmr->TC) dt = tmr->TC - tmr->mr; \
				else dt = tmr->TC + (0xFFFFFFFF - tmr->mr); \
				if ((dt + i1)< ts->interval)	tmr->mr += ts->interval; \
				else { \
					ts->dtfix = dt; \
					ts->intfix = ts->interval; \
					tmr->mr = tmr->TC + i2; \
				}	\
}				

void Init_TCS(volatile TIMER_CONTROL_STRUCT* TCS,u8 t,u8 mr,TTimerHandler h){
	LPC_TIM_TypeDef       * pT;
	TCS->handler = h;
	pT = 0;
	switch (t) {	
		case 0:pT=LPC_TIM0; break;
		case 1:pT=LPC_TIM1; break;		
		case 2:pT=LPC_TIM2; break;
		case 3:pT=LPC_TIM3; break;
	}
	if (!pT) return;
	TCS->pTC=&(pT->TC);
 	switch (mr){
		case 0:	TCS->pMR=&(pT->MR0); break;
		case 1: TCS->pMR=&(pT->MR1); break;
		case 2:	TCS->pMR=&(pT->MR2); break;
		case 3: TCS->pMR=&(pT->MR3); break;
	}
	switch (t*10+mr) {
		case 00: T0MR0 = TCS; break;
		case 01: T0MR1 = TCS; break;
		case 02: T0MR2 = TCS; break;
		case 03: T0MR3 = TCS; break;

		case 10: T1MR0 = TCS; break;
		case 11: T1MR1 = TCS; break;
		case 12: T1MR2 = TCS; break;
		case 13: T1MR3 = TCS; break;

		case 20: T2MR0 = TCS; break;
		case 21: T2MR1 = TCS; break;
		case 22: T2MR2 = TCS; break;
		case 23: T2MR3 = TCS; break;

		case 30: T3MR0 = TCS; break;
		case 31: T3MR1 = TCS; break;
		case 32: T3MR2 = TCS; break;
		case 33: T3MR3 = TCS; break;
	}
}

//void InitTimer(u8 num)
// основная инициализации таймера
// u8 num		- номер порта
// инициализирует таймер с параметрами по умолчанию
// TC считает по кругу (не сбрасывается)
// инициализируются все 4 канала MR
// приоритет равен num
// этой инициализацией будет инициализироваться таймер 0 для таймеров движения по осям и прямой
// таймер 1 НЕЛЬЗЯ !!! инициализировать этой процедурой 
void InitTimer(u8 num){
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct;
	LPC_TIM_TypeDef       * pT;
	IRQn_Type IRQn;
	pT = 0;
	// выбор ссылки на управляющую структуру и номер IRQ
	switch (num) {	
		case 0:pT=LPC_TIM0; IRQn=TIMER0_IRQn; break;
		case 1:pT=LPC_TIM1; IRQn=TIMER1_IRQn; break;
		case 2:pT=LPC_TIM2; IRQn=TIMER2_IRQn; break;
		case 3:pT=LPC_TIM3; IRQn=TIMER3_IRQn; break;
	}
	if (pT==0) return;
//  интервал счета 0,04 мкс * pv
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL; 
	TIM_ConfigStruct.PrescaleValue	= (u32)1/*pv*/;	
	TIM_Init(pT, TIM_TIMER_MODE,&TIM_ConfigStruct);

	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	TIM_MatchConfigStruct.ResetOnMatch = FALSE;
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
	TIM_MatchConfigStruct.MatchValue   = (u32)2500000/*mv*/; 
	TIM_MatchConfigStruct.MatchChannel = 0;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);
	TIM_MatchConfigStruct.MatchChannel = 1;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

	TIM_MatchConfigStruct.MatchChannel = 2;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

	TIM_MatchConfigStruct.MatchChannel = 3;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);
	NVIC_EnableIRQ(IRQn);
	NVIC_SetPriority(IRQn, num);
	TIM_Cmd(pT,ENABLE);
}

// инициализация таймера врежиме сброса по прерыванию и только с MR0
void InitTimer1(u8 num){
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct;
	LPC_TIM_TypeDef       * pT;
	IRQn_Type IRQn;
	pT = 0;
	// выбор ссылки на управляющую структуру и номер IRQ
	switch (num) {	
		case 0:pT=LPC_TIM0; IRQn=TIMER0_IRQn; break;
		case 1:pT=LPC_TIM1; IRQn=TIMER1_IRQn; break;
		case 2:pT=LPC_TIM2; IRQn=TIMER2_IRQn; break;
		case 3:pT=LPC_TIM3; IRQn=TIMER3_IRQn; break;
	}
	if (pT==0) return;
//  интервал счета 0,04 мкс * pv
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL; 
	TIM_ConfigStruct.PrescaleValue	= (u32)1/*pv*/;	
	TIM_Init(pT, TIM_TIMER_MODE,&TIM_ConfigStruct);

	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
//	TIM_MatchConfigStruct.ResetOnMatch = FALSE;
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
	TIM_MatchConfigStruct.MatchValue   = (u32)2500000/*mv*/; 
	
	TIM_MatchConfigStruct.MatchChannel = 0;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);
	
//	TIM_MatchConfigStruct.MatchChannel = 1;
//	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

//	TIM_MatchConfigStruct.MatchChannel = 2;
//	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

//	TIM_MatchConfigStruct.MatchChannel = 3;
//	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

	NVIC_EnableIRQ(IRQn);
	NVIC_SetPriority(IRQn, num);
	TIM_Cmd(pT,ENABLE);
}


void TIMER0_IRQHandler(void)
{
	u32 dt,ir;
	
  ir = LPC_TIM0->IR;
	if (ir & TIM_IR_CLR(TIM_MR0_INT))
	{	// отработка таймера
//	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
		LPC_TIM0->IR = TIM_IR_CLR(TIM_MR0_INT);	
		if (T0MR0) {
			if (T0MR0->enabled) {
				(*(T0MR0->handler))();
				NEXT_INT(LPC_TIM0,MR0,T0MR0,35,15);
			}
		}
	}
	if (ir & TIM_IR_CLR(TIM_MR1_INT))
	{	// отработка таймера
		LPC_TIM0->IR = TIM_IR_CLR(TIM_MR1_INT);		
		if (T0MR1) {
			if (T0MR1->enabled) {
				(*(T0MR1->handler))();
				NEXT_INT(LPC_TIM0,MR1,T0MR1,35,15);
			}
		}
	}
	if (ir & TIM_IR_CLR(TIM_MR2_INT))
	{	// отработка таймера
		LPC_TIM0->IR = TIM_IR_CLR(TIM_MR2_INT);	
		if (T0MR2) {
			if (T0MR2->enabled) {
				(*(T0MR2->handler))();
				NEXT_INT(LPC_TIM0,MR2,T0MR2,35,15);
			}
		}
	}
	if (ir & TIM_IR_CLR(TIM_MR3_INT))
	{	// отработка таймера
		LPC_TIM0->IR = TIM_IR_CLR(TIM_MR3_INT);	
		if (T0MR3) {
			if (T0MR3->enabled) {
				(*(T0MR3->handler))();
				NEXT_INT(LPC_TIM0,MR3,T0MR3,35,15);
			}
		}
	}
	
}

// новый
void TIMER1_IRQHandler(void)
{
	// это жесткая заточка таймера 1 под подсчет задержек
	// инициализироваться таймер должен так
	//							 num	ROM	emr0	emr1	emr2	emr3	pr
	// InitTimerMod1(1,		1,	1,		0,		0,		0,		1);
	LPC_TIM1->IR = TIM_IR_CLR(TIM_MR0_INT); // сброс
	// тут вызов
	TI_Handler();
/*
	// этот код нужно открыть если использовать таймер 1 с циклическим счетом TC 
	// и со всеми регистрами MR
	u32 dt,ir;
	ir = LPC_TIM1->IR;
	if (ir & TIM_IR_CLR(TIM_MR0_INT))
	{	// отработка таймера
		LPC_TIM1->IR = TIM_IR_CLR(TIM_MR0_INT);
		if (T1MR0) {
			if (T1MR0->enabled) {
				(*(T1MR0->handler))();
				NEXT_INT(LPC_TIM1,MR0,T1MR0,35,15);
			}
		}
	}
	if (ir & TIM_IR_CLR(TIM_MR1_INT)) // проверка
	{	// отработка таймера
		LPC_TIM1->IR = TIM_IR_CLR(TIM_MR1_INT); // сброс
		if (T1MR1) {
			if (T1MR1->enabled) {
				(*(T1MR1->handler))();
				NEXT_INT(LPC_TIM1,MR1,T1MR1,35,15);
			}
		}
	}

	if (ir & TIM_IR_CLR(TIM_MR2_INT))
	{	// отработка таймера
		LPC_TIM1->IR = TIM_IR_CLR(TIM_MR2_INT); // сброс
		if (T1MR2) {
			if (T1MR2->enabled) {
				(*(T1MR2->handler))();
				NEXT_INT(LPC_TIM1,MR2,T1MR2,35,15);
			}
		}
	}

	if (ir & TIM_IR_CLR(TIM_MR3_INT))
	{	// отработка таймера
		LPC_TIM1->IR = TIM_IR_CLR(TIM_MR3_INT); // сброс
		if (T1MR3) {
			if (T1MR3->enabled) {
				(*(T1MR3->handler))();
				NEXT_INT(LPC_TIM1,MR3,T1MR3,35,15);
			}
		}
	}
*/	
	
}

// новый
void TIMER2_IRQHandler(void)
{
	u32 dt;
	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T2MR0) {
			if (T2MR0->enabled) {
				(*(T2MR0->handler))();
				NEXT_INT(LPC_TIM2,MR0,T2MR0,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T2MR1) {
			if (T2MR1->enabled) {
				(*(T2MR1->handler))();
				NEXT_INT(LPC_TIM2,MR1,T2MR1,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T2MR2) {
			if (T2MR2->enabled) {
				(*(T2MR2->handler))();
				NEXT_INT(LPC_TIM2,MR2,T2MR2,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T2MR3) {
			if (T2MR3->enabled) {
				(*(T2MR3->handler))();
				NEXT_INT(LPC_TIM2,MR3,T2MR3,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR3_INT);
	}
}


// новый
void TIMER3_IRQHandler(void)
{
	u32 dt;
	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T3MR0) {
			if (T3MR0->enabled) {
				(*(T3MR0->handler))();
				NEXT_INT(LPC_TIM3,MR0,T3MR0,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T3MR1) {
			if (T3MR1->enabled) {
				(*(T3MR1->handler))();
				NEXT_INT(LPC_TIM3,MR1,T3MR1,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T3MR2) {
			if (T3MR2->enabled) {
				(*(T3MR2->handler))();
				NEXT_INT(LPC_TIM3,MR2,T3MR2,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T3MR3) {
			if (T3MR3->enabled) {
				(*(T3MR3->handler))();
				NEXT_INT(LPC_TIM3,MR3,T3MR3,35,15);
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR3_INT);
	}
}
