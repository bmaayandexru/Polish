#ifndef __MOTOR_X_H__
#define __MOTOR_X_H__

#include "Defs.h"

#include "Motors.h"
#include "Timers.h"

extern volatile TIMER_CONTROL_STRUCT tcs_MotorX; 	// структура управления таймером движения радиальным двигателем 
extern volatile TFMC 	mc_X;
extern volatile TFMS 	ms_X;

void	MotorX_Handler(void);

#endif
//#ifndef __MOTOR_X_H__



