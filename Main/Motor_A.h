#ifndef __MOTOR_A_H__
#define __MOTOR_A_H__

#include "Defs.h"

#ifdef __SAW__
#include "Motors.h"
#include "Timers.h"

extern TIMER_CONTROL_STRUCT tcs_MotorA; 	// структура управления таймером движения радиальным двигателем 
extern TMC 	mc_A;
extern TMS 	ms_A;

extern	u8 * pValueLuft; // значение люфта
extern	u8 * pFLuft;
extern	u8 * pBLuft;

u8 Compensation(void);
void	MotorA_Handler(void);

#endif
// #ifdef __SAW__
#endif
//#ifndef __MOTOR_A_H__
