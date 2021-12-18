//#include <string.h>
#include "Defs.h"
#include "StaticPins.h"
#include "VirtualPins.h"
#include "ti.h"
#include "regs.h"
#include "KeyPad.h"

typedef struct tagDRB {
	u8		DState;		// состояние для выходных пинов после дребезга
	u8		iTime;		// индекс временного интервала
} TDRB;

typedef TDRB TaDRB[VIRTUAL_PINTAB_SIZE];




TaDRB adrb = {
//	Dstate, iTime
	{		0,		0},	// MOTOR_R_STEP
	{		0,		0}, // MOTOR_R_DIR
	{		0,		0}, // MOTOR_R_EN
	{		0,		0}, // MOTOR_A_STEP
	{		0,		0}, // MOTOR_A_DIR
	{		0,		0}, // MOTOR_A_EN
	{		0,		0}, // MOTOR_Vu_STEP
	{		0,		0},	// MOTOR_Vu_DIR		
	{		0,		0},	// MOTOR_Vu_EN
	{		0,		0},	// MOTOR_Vd_STEP
	{		0,		0},	// MOTOR_Vd_DIR
	{		0,		0},	// MOTOR_Vd_EN
	{		0,		0},
	{		0,		0},
	{		0,		0},
	{		0,		0},
	{		0,		0},
	{		0,		0},
	{		0,		0},
	{		0,		0},

	{		0,		timeIN1},	 // BTN_MOTOR_R_DIR
	{		0,		timeIN2},	 // BTN_MOTOR_R_BACK
	{		0,		timeIN3},	 // BTN_MOTOR_A_DIR
	{		0,		timeIN4},	 // BTN_MOTOR_A_BACK
	{		0,		timeIN5},	 // BTN_SET_POINT	BTN_SET_PAUSE
	{		0,		timeIN6},  //	BTN_LOW_SPEED  	BTN_SET_PAUSE_OFF_TROS
	{		0,		timeIN7},
	{		0,		timeIN8},
	{		0,		timeIN9},
	{		0,		timeIN10},	 // SENS_MOTOR_A
	{		0,		timeIN11},	 // SENS_MOTOR_R
	{		0,		timeIN12},	 // SENS_MOTOR_Vu
	{		0,		timeIN13},	 // CRASH_WATER
	{		0,		timeIN14},	 // SENS_MOTOR_Vd
	{		0,		timeIN15},	 // CRUSH_POWER
	{		0,		timeIN16}	 // CRUSH_TROS

	};


TaVPIN *pvPins;
TaVQPIN aVQPIN;	
/*
*/

TErrHandler pErrHandler = 0;
TPinError pe;

void SetPinsErrHandler(TErrHandler eh){
	pErrHandler = eh;
}
//void (*pErrorFunction)(TPinError * pe); 
// инициализация по умолчанию если возможно
// возможно если в таблице vPin проставлены значения смещений
// и в aPin проставлены значения направлений по умолчанию
void DefaultInitPins(void) {
	u16 i = 0;
	for (i = 0; i < VIRTUAL_PINTAB_SIZE; i++) {
		if ((*pvPins)[i].nPin !=0xFF) {
			if (aPin[(*pvPins)[i].nPin].DIR!=0xFF) InitPin(i);
		}
	}
}

// формирование таблицы для бытрого доступа к пинам
void 	FormQPinTable(void){
	u16 i = 0,ofs;
	for (i = 0; i < VIRTUAL_PINTAB_SIZE; i++) {
		// фиксируем смещение в таблице статических пинов 
		// чтобы не таскать по всему алгоритму
		ofs = (*pvPins)[i].nPin; 
		// уравниваем инверсии
		aVQPIN[i].Inv = (*pvPins)[i].Inv;
		if (aVQPIN[i].Inv) {
			aVQPIN[i].ClrAddr = &(aPin[ofs].pPort->FIOSET);
			aVQPIN[i].SetAddr = &(aPin[ofs].pPort->FIOCLR);
		}	else {
			aVQPIN[i].ClrAddr = &(aPin[ofs].pPort->FIOCLR);
			aVQPIN[i].SetAddr = &(aPin[ofs].pPort->FIOSET);
		}
		aVQPIN[i].GetAddr = &(aPin[ofs].pPort->FIOPIN);
		aVQPIN[i].Mask = aPin[ofs].mPin;
	}
}	

void CallErrorHandler(u8 n,u16 Code){
	if (pErrHandler) { 
		// запонить структуру возврвщаемую в обработчике ошибки
		// и вызвать обработчик
		pe.ErrorCode = Code;	// 
		pe.vNum = n;
		pe.sNum = (*pvPins)[n].nPin;
		if ((*pvPins)[n].nPin < PinCount) {
			// через switch
			if (aPin[(*pvPins)[n].nPin].pPort==LPC_GPIO0) pe.sPort = 0; else
			if (aPin[(*pvPins)[n].nPin].pPort==LPC_GPIO1) pe.sPort = 1; else
			if (aPin[(*pvPins)[n].nPin].pPort==LPC_GPIO2) pe.sPort = 2; else
			if (aPin[(*pvPins)[n].nPin].pPort==LPC_GPIO3) pe.sPort = 3; else
				pe.sPort = 0xFF;
			pe.sPin = aPin[(*pvPins)[n].nPin].mPin;
			pe.Dir  = aPin[(*pvPins)[n].nPin].DIR;
			pe.Inv	= (*pvPins)[n].Inv;
		} else {
			pe.sPort = 0xFF;
			pe.sPin = 0xFF;
			pe.Dir  = 0xFF;
			pe.Inv	= 0xFF;
		}
	 	(*pErrHandler)(&pe);
	}
}

// инициализация виртуального пина
BOOL InitPin(u8 n){
	if ((*pvPins)[n].nPin < PinCount) {
//		Msg("%d %d %d",n,(*pvPins)[n].nPin,(*pvPins)[n].Inv);
		switch (aPin[(*pvPins)[n].nPin].DIR) {
			case DIR_OUT:
//				Msg("O\r\n");
				aPin[(*pvPins)[n].nPin].pPort->FIODIR |= (aPin[(*pvPins)[n].nPin].mPin);
				(*pvPins)[n].State = 0;
				SetPin(n);	// устанавливаем и
				ClrPin(n); 	// сбрасываем бит
				return TRUE;
//				break;
			case DIR_IN:
//				Msg("I\r\n");
				aPin[(*pvPins)[n].nPin].pPort->FIODIR &= ~(aPin[(*pvPins)[n].nPin].mPin);
				return TRUE;
//				break;
			default : CallErrorHandler(n,0x11);
		}
	} else {
		CallErrorHandler(n,0x10);
	}
	return FALSE;
}
// установка виртуального пина
BOOL SetPin(u8 n){
	if ((*pvPins)[n].nPin!=0xFF) { // инициализация виртуального пина
		if	(aPin[(*pvPins)[n].nPin].DIR==DIR_OUT)  // направление инициализации статического пина
		{
			if (!(*pvPins)[n].State) {
				(*pvPins)[n].State = 1;
				if ((*pvPins)[n].Inv) 
				     aPin[(*pvPins)[n].nPin].pPort->FIOPIN &= ~(aPin[(*pvPins)[n].nPin].mPin);
			   	else aPin[(*pvPins)[n].nPin].pPort->FIOPIN |=  (aPin[(*pvPins)[n].nPin].mPin);
			}
		   	return TRUE;
		} else {
			CallErrorHandler(n,0x21);
		}
	} else {
		CallErrorHandler(n,0x20);
	}
	return FALSE;
}

void QSetPin(u8 n){
	if (!(*pvPins)[n].State) { 	//*
		(*pvPins)[n].State = 1;		//*
		if ((*pvPins)[n].Inv) 
		     aPin[(*pvPins)[n].nPin].pPort->FIOCLR = aPin[(*pvPins)[n].nPin].mPin;
	   	else aPin[(*pvPins)[n].nPin].pPort->FIOSET =  aPin[(*pvPins)[n].nPin].mPin;
	}														//*
}

void Q1SetPin(u8 n){
		*(aVQPIN[n].SetAddr) = aVQPIN[n].Mask;
}
// сброс виртуального пина
BOOL ClrPin(u8 n){
	if ((*pvPins)[n].nPin!=0xFF) { // инициализация виртуального пина
		if(aPin[(*pvPins)[n].nPin].DIR==DIR_OUT)  // направление инициализации статического пина
		{
			if ((*pvPins)[n].State) {
				(*pvPins)[n].State = 0;
				if ((*pvPins)[n].Inv) 
					// инверсия
					aPin[(*pvPins)[n].nPin].pPort->FIOPIN |=  (aPin[(*pvPins)[n].nPin].mPin);
			   	else
					aPin[(*pvPins)[n].nPin].pPort->FIOPIN &= ~(aPin[(*pvPins)[n].nPin].mPin);
			}
		   	return TRUE;
		} else {
			CallErrorHandler(n,0x31);
		}
	} else {
		CallErrorHandler(n,0x30);
	}
	return FALSE;
}

void QClrPin(u8 n){
	if ((*pvPins)[n].State) {
		(*pvPins)[n].State = 0;
		if ((*pvPins)[n].Inv) 
			// инверсия
			aPin[(*pvPins)[n].nPin].pPort->FIOPIN |=  (aPin[(*pvPins)[n].nPin].mPin);
	   	else
			aPin[(*pvPins)[n].nPin].pPort->FIOPIN &= ~(aPin[(*pvPins)[n].nPin].mPin);
	}
}

void Q1ClrPin(u8 n){
		*(aVQPIN[n].ClrAddr) = aVQPIN[n].Mask;
}

u32 GetPin(u8 n){
	if ((*pvPins)[n].nPin!=0xFF) { // инициализация виртуального пина
		if(aPin[(*pvPins)[n].nPin].DIR==DIR_IN) // направление инициализации статического пина
		{
			if ((*pvPins)[n].Inv) {
				// инверсия
//				return (~(aPin[(*pvPins)[n].nPin].pPort->FIOPIN) & aPin[(*pvPins)[n].nPin].mPin);
				if (~(aPin[(*pvPins)[n].nPin].pPort->FIOPIN) & aPin[(*pvPins)[n].nPin].mPin) 
				 	 (*pvPins)[n].State = 1;
				else (*pvPins)[n].State = 0;
				return (*pvPins)[n].State;
			} else {
//				return (aPin[(*pvPins)[n].nPin].pPort->FIOPIN & aPin[(*pvPins)[n].nPin].mPin);
				if (aPin[(*pvPins)[n].nPin].pPort->FIOPIN & aPin[(*pvPins)[n].nPin].mPin) 
				 	 (*pvPins)[n].State = 1;
				else (*pvPins)[n].State = 0;
				return (*pvPins)[n].State;
			}
		} else {
			if(aPin[(*pvPins)[n].nPin].DIR==DIR_OUT) { 
				return (*pvPins)[n].State;
			} else CallErrorHandler(n,0x41);
		}
	} else {
		CallErrorHandler(n,0x40);
	}
	return 0xFFFFFFFF; 
}

void	Drebezg(u8 n){
	if (((*pvPins)[n].State)!=(adrb[n].DState)) {
		if (StartedTime(adrb[n].iTime)) {
			// время запущено
			if (GetTime(adrb[n].iTime) > tiMksToTick((*pDrDelay)*100)) { 
				// промежуток выполнен
				// уравниваем состояния
				adrb[n].DState = (*pvPins)[n].State;
				// останавливаем время
				StopTime(adrb[n].iTime);
			}
		} else {
			// время не запущено запускаем
			StartTime(adrb[n].iTime);
			// и ничего не делаем
		}
	} else {
		// при равенстве State и DState останавливаем время
		StopTime(adrb[n].iTime);
	} 

	// заглушка чтобы работало по старому
	//(*pvPins)[n].DState = (*pvPins)[n].State;
}

u32 QGetPin(u8 n){
	if (aPin[(*pvPins)[n].nPin].DIR==DIR_IN) {
		// опрос входного пина
		if ((*pvPins)[n].Inv) {
			// инверсия
//			return (~(aPin[(*pvPins)[n].nPin].pPort->FIOPIN) & aPin[(*pvPins)[n].nPin].mPin);
			if (~(aPin[(*pvPins)[n].nPin].pPort->FIOPIN) & aPin[(*pvPins)[n].nPin].mPin) 
			 	 (*pvPins)[n].State = 1;
			else (*pvPins)[n].State = 0;
			// алгоритм дребезга
			Drebezg(n);
			return adrb[n].DState;
		} else {
//			return (aPin[(*pvPins)[n].nPin].pPort->FIOPIN & aPin[(*pvPins)[n].nPin].mPin);
			if (aPin[(*pvPins)[n].nPin].pPort->FIOPIN & aPin[(*pvPins)[n].nPin].mPin) 
			 	 (*pvPins)[n].State = 1;
			else (*pvPins)[n].State = 0;
			// алгоритм дребезга
			Drebezg(n);
			return adrb[n].DState;
		}
	} else {
		if (aPin[(*pvPins)[n].nPin].DIR==DIR_OUT) {
			// опрос выходного пина
			return (*pvPins)[n].State;
		} else return 0;
	}
}

u32 Q1GetPin(u8 n){
	// без дребезга !!!
	if (aVQPIN[n].Inv) {
		return !(*(aVQPIN[n].GetAddr) & aVQPIN[n].Mask); 
	} else {
		return (*(aVQPIN[n].GetAddr) & aVQPIN[n].Mask); 
	}
}

void ClrGetPin(u8 n){
	(*pvPins)[n].State = 0;
	adrb[n].DState = 0;	
}	
// следующий набор функций реализован на всякий случай
// чтение направления виртуального пина
u8 GetPinDir(u8 n){
	if ((*pvPins)[n].nPin!=0xFF) {
		// пин используется - возвращаем направление
		return (aPin[(*pvPins)[n].nPin].DIR);
	} else {
		CallErrorHandler(n,0x50);
	}
	return 0xFF;
}

u8 GetPinInv(u8 n){
	if ((*pvPins)[n].nPin!=0xFF) {
		// пин используется
		return ((*pvPins)[n].Inv); // возвращвем инверсию
	} else {
		CallErrorHandler(n,0x70);
	}
	return 0xFF;
}

void SetPinInv(u8 n,u8 i){
	if ((*pvPins)[n].nPin!=0xFF) {
		// пин используется
		if (aPin[(*pvPins)[n].nPin].DIR!=0xFF) {
			// пин инициализирован
			(*pvPins)[n].Inv = i; // изменяем значение инверсии
			if (aPin[(*pvPins)[n].nPin].DIR==DIR_OUT) {
				// если пин выходной
				// устанавливаем и сбрасываем его
				// тогда поле State примет корректное значение
				QSetPin(n);		  
				QClrPin(n);
			}
		} else { 
	 		CallErrorHandler(n,0x82);
		}
	} else {
		// ошибка
		CallErrorHandler(n,0x80);
	}
}

void InitVirtualPins (void) {
	u8 i;
	for (i=0;i<PinCount;i++) InitPin(i);
}

