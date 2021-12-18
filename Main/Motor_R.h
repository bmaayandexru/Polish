#ifndef __MOTOR_R_H__
#define __MOTOR_R_H__

#include "Defs.h"

#ifdef __SAW__
#include "Motors.h"
#include "Timers.h"

extern TIMER_CONTROL_STRUCT tcs_MotorR; 	// структура управления таймером движения радиальным двигателем 
extern TMC 	mc_R;
extern TMS 	ms_R;

void	MotorR_Handler(void);

#endif
// #ifdef __SAW__
#endif
//#ifndef __MOTOR_R_H__
