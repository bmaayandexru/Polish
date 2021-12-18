#include "Defs.h"
#include "lpc17xx_timer.h"
#include "Timers.h"
#include "msg.h"

TIMER_CONTROL_STRUCT *T0MR0=0,*T0MR1=0,*T0MR2=0,*T0MR3=0;
TIMER_CONTROL_STRUCT *T1MR0=0,*T1MR1=0,*T1MR2=0,*T1MR3=0;
TIMER_CONTROL_STRUCT *T2MR0=0,*T2MR1=0,*T2MR2=0,*T2MR3=0;
TIMER_CONTROL_STRUCT *T3MR0=0,*T3MR1=0,*T3MR2=0,*T3MR3=0;

//#define CHECK0(v) ( (v==0) ? 1 : v)
// ПРОБУЕМ !!!!
//#define CHECK0(v) ( (v==0) ? 1 : v)
// ОТЛАДКА !!!
//#define CHECK0(v) ( (v<5000) ? 5000 : v)

#define CHECK1(v) ( (v>2500000) ? 2500000 : v)
#define CHECK0(v) ( (v<15) ? 15 : CHECK1(v))

/*
u64 CHECK0(u64 v){
	if (v < 1) {
		return 1;
	} else {
		if (v > 2500000){
			return 2500000;
		}
		else return v;
	}
}
*/

void Init_TCS(TIMER_CONTROL_STRUCT* TCS,u8 t,u8 mr,TTimerHandler h){
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
	//Msg("T0MR0 %d \r\n",T0MR0);
}


void InitTimer(u8 num)/*, u32 pv,u32 mv)*/{
	// инициализация таймера Timer0 с интервалом 10 мкс 
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
	TIM_MatchConfigStruct.MatchValue   = (u32)0/*mv*/; 
	TIM_MatchConfigStruct.MatchChannel = 0;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

	TIM_MatchConfigStruct.MatchChannel = 1;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

	TIM_MatchConfigStruct.MatchChannel = 2;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);

	TIM_MatchConfigStruct.MatchChannel = 3;
	TIM_ConfigMatch(pT,&TIM_MatchConfigStruct);
	NVIC_SetPriority(IRQn, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(IRQn);
	TIM_Cmd(pT,ENABLE);
	//Msg("num %d MCR %d\r\n",num,pT->MCR);
}

/*
void InitTimer0(u32 pv,u32 mv){
	// инициализация таймера Timer0 с интервалом 10 мкс 
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct;

//  интервал счета 0,04 мкс * pv
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL; 
	TIM_ConfigStruct.PrescaleValue	= pv;	
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);

	TIM_MatchConfigStruct.MatchChannel = 0;
	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
	TIM_MatchConfigStruct.MatchValue   = mv; 

	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(TIMER0_IRQn);
	TIM_Cmd(LPC_TIM0,ENABLE);
}
*/
/*
//новый
void TIMER0_IRQHandler(void)
{
	u8 IWMR0 = 0;
	u8 IWMR1 = 0;
	u8 IWMR2 = 0;
	u8 IWMR3 = 0;
	// MR0
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T0MR0) {
			if (T0MR0->enabled) {
				IWMR0 = 1;
				(*(T0MR0->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	}
	// MR1
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T0MR1) {
			if (T0MR1->enabled) {
				IWMR1 = 1;
				(*(T0MR1->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR1_INT);
	}
	// MR2
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T0MR2) {
			if (T0MR2->enabled) {
				IWMR2 = 1;
				(*(T0MR2->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR2_INT);
	}
	// MR3
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T0MR3) {
			if (T0MR3->enabled) {
				IWMR3 = 1;
				(*(T0MR3->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR3_INT);
	}
	if (IWMR0) LPC_TIM0->MR0 = LPC_TIM0->TC + CHECK0(T0MR0->interval) ;
	if (IWMR1) LPC_TIM0->MR1 = LPC_TIM0->TC + CHECK0(T0MR1->interval) ;
	if (IWMR2) LPC_TIM0->MR2 = LPC_TIM0->TC + CHECK0(T0MR2->interval) ;
	if (IWMR3) LPC_TIM0->MR3 = LPC_TIM0->TC + CHECK0(T0MR3->interval) ;
}
*/

// старый
void TIMER0_IRQHandler(void)
{
//	static u8 f=1;
	static u32 m_tc;

	m_tc = LPC_TIM0->TC; 
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	// if ((LPC_TIM0->IR) & 1) сработало прерывание по LPC_TIM0->MR0 
	{	// отработка таймера
		if (T0MR0) {
			if (T0MR0->enabled) {
				(*(T0MR0->handler))();
				if (T0MR0->enabled)
					LPC_TIM0->MR0 = m_tc + T0MR0->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
		//LPC_TIM0->IR = (1<<0); // сброс прерывания по MR0
	}
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR1_INT)== SET)
	// if ((LPC_TIM0->IR) & (1<<1)) сработало прерывание по LPC_TIM0->MR1 
	{	// отработка таймера
		if (T0MR1) {
			if (T0MR1->enabled) {
				(*(T0MR1->handler))();
				if (T0MR1->enabled)
					LPC_TIM0->MR1 = m_tc + T0MR1->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR1_INT);
		//LPC_TIM0->IR = (1<<1); // сброс прерывания по MR1
	}
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T0MR2) {
			if (T0MR2->enabled) {
				(*(T0MR2->handler))();
				if (T0MR2->enabled)
					LPC_TIM0->MR2 = m_tc + T0MR2->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR2_INT);
	}
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T0MR3) {
			if (T0MR3->enabled) {
				(*(T0MR3->handler))();
				if (T0MR3->enabled)
					LPC_TIM0->MR3 = m_tc + T0MR3->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM0, TIM_MR3_INT);
	}
}

/*
// старый
void TIMER1_IRQHandler(void)
{
	static u32 m_tc;

	m_tc = LPC_TIM1->TC; 
	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T1MR0) {
			if (T1MR0->enabled) {
				(*(T1MR0->handler))();
				if (T1MR0->enabled)
					LPC_TIM1->MR0 = m_tc + T1MR0->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T1MR1) {
			if (T1MR1->enabled) {
				(*(T1MR1->handler))();
				if (T1MR1->enabled)
					LPC_TIM1->MR1 = m_tc + T1MR1->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T1MR2) {
			if (T1MR2->enabled) {
				(*(T1MR2->handler))();
				if (T1MR2->enabled)
					LPC_TIM1->MR2 = m_tc + T1MR2->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T1MR3) {
			if (T1MR3->enabled) {
				(*(T1MR3->handler))();
				if (T1MR3->enabled)
					LPC_TIM1->MR3 = m_tc + T1MR3->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR3_INT);
	}

}
*/

// новый
void TIMER1_IRQHandler(void)
{
	u8 IWMR0 = 0;
	u8 IWMR1 = 0;
	u8 IWMR2 = 0;
	u8 IWMR3 = 0;

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T1MR0) {
			if (T1MR0->enabled) {
				IWMR0 = 1;
				(*(T1MR0->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T1MR1) {
			if (T1MR1->enabled) {
				IWMR1 = 1;
				(*(T1MR1->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T1MR2) {
			if (T1MR2->enabled) {
				IWMR2 = 1;
				(*(T1MR2->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM1, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T1MR3) {
			if (T1MR3->enabled) {
				IWMR3 = 1;
				(*(T1MR3->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM1, TIM_MR3_INT);
	}
//*********************
	if (IWMR0) LPC_TIM1->MR0 = LPC_TIM1->TC + CHECK0(T1MR0->interval) ;
	if (IWMR1) LPC_TIM1->MR1 = LPC_TIM1->TC + CHECK0(T1MR1->interval) ;
	if (IWMR2) LPC_TIM1->MR2 = LPC_TIM1->TC + CHECK0(T1MR2->interval) ;
	if (IWMR3) LPC_TIM1->MR3 = LPC_TIM1->TC + CHECK0(T1MR3->interval) ;
}
/*
void TIMER2_IRQHandler(void)
{
	static u32 m_tc;

	m_tc = LPC_TIM2->TC; 
	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T2MR0) {
			if (T2MR0->enabled) {
				(*(T2MR0->handler))();
				if (T2MR0->enabled)
					LPC_TIM2->MR0 = m_tc + T2MR0->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T2MR1) {
			if (T2MR1->enabled) {
				(*(T2MR1->handler))();
				if (T2MR1->enabled)
					LPC_TIM2->MR1 = m_tc + T2MR1->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T2MR2) {
			if (T2MR2->enabled) {
				(*(T2MR2->handler))();
				if (T2MR2->enabled)
					LPC_TIM2->MR2 = m_tc + T2MR2->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T2MR3) {
			if (T2MR3->enabled) {
				(*(T2MR3->handler))();
				if (T2MR3->enabled)
					LPC_TIM2->MR3 = m_tc + T2MR3->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR3_INT);
	}

}
*/
// новый
void TIMER2_IRQHandler(void)
{
	u8 IWMR0 = 0;
	u8 IWMR1 = 0;
	u8 IWMR2 = 0;
	u8 IWMR3 = 0;

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T2MR0) {
			if (T2MR0->enabled) {
				IWMR0 = 1;
				(*(T2MR0->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T2MR1) {
			if (T2MR1->enabled) {
				IWMR1 = 1;
				(*(T2MR1->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T2MR2) {
			if (T2MR2->enabled) {
				IWMR2 = 1;
				(*(T2MR2->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM2, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T2MR3) {
			if (T2MR3->enabled) {
				IWMR3 = 1;
				(*(T2MR3->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM2, TIM_MR3_INT);
	}
	
	if (IWMR0) LPC_TIM2->MR0 = LPC_TIM2->TC + CHECK0(T2MR0->interval) ;
	if (IWMR1) LPC_TIM2->MR1 = LPC_TIM2->TC + CHECK0(T2MR1->interval) ;
	if (IWMR2) LPC_TIM2->MR2 = LPC_TIM2->TC + CHECK0(T2MR2->interval) ;
	if (IWMR3) LPC_TIM2->MR3 = LPC_TIM2->TC + CHECK0(T2MR3->interval) ;
}

/*
// старый
void TIMER3_IRQHandler(void)
{
	static u32 m_tc;

	m_tc = LPC_TIM3->TC; 
	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T3MR0) {
			if (T3MR0->enabled) {
				(*(T3MR0->handler))();
				if (T3MR0->enabled)
					LPC_TIM3->MR0 = m_tc + T3MR0->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T3MR1) {
			if (T3MR1->enabled) {
				(*(T3MR1->handler))();
				if (T3MR1->enabled)
					LPC_TIM3->MR1 = m_tc + T3MR1->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T3MR2) {
			if (T3MR2->enabled) {
				(*(T3MR2->handler))();
				if (T3MR2->enabled)
					LPC_TIM3->MR2 = m_tc + T3MR2->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T3MR3) {
			if (T3MR3->enabled) {
				(*(T3MR3->handler))();
				if (T3MR3->enabled)
					LPC_TIM3->MR3 = m_tc + T3MR3->interval;
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR3_INT);
	}
}
*/
// новый
void TIMER3_IRQHandler(void)
{
	u8 IWMR0 = 0;
	u8 IWMR1 = 0;
	u8 IWMR2 = 0;
	u8 IWMR3 = 0;

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR0_INT)== SET)
	{	// отработка таймера
		if (T3MR0) {
			if (T3MR0->enabled) {
				IWMR0 = 1;
				(*(T3MR0->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR0_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR1_INT)== SET)
	{	// отработка таймера
		if (T3MR1) {
			if (T3MR1->enabled) {
				IWMR1 = 1;
				(*(T3MR1->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR1_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR2_INT)== SET)
	{	// отработка таймера
		if (T3MR2) {
			if (T3MR2->enabled) {
				IWMR2 = 1;
				(*(T3MR2->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR2_INT);
	}

	if (TIM_GetIntStatus(LPC_TIM3, TIM_MR3_INT)== SET)
	{	// отработка таймера
		if (T3MR3) {
			if (T3MR3->enabled) {
				IWMR3 = 1;
				(*(T3MR3->handler))();
			}
		}
		TIM_ClearIntPending(LPC_TIM3, TIM_MR3_INT);
	}
	
	if (IWMR0) LPC_TIM3->MR0 = LPC_TIM3->TC + CHECK0(T3MR0->interval) ;
	if (IWMR1) LPC_TIM3->MR1 = LPC_TIM3->TC + CHECK0(T3MR1->interval) ;
	if (IWMR2) LPC_TIM3->MR2 = LPC_TIM3->TC + CHECK0(T3MR2->interval) ;
	if (IWMR3) LPC_TIM3->MR3 = LPC_TIM3->TC + CHECK0(T3MR3->interval) ;
}
