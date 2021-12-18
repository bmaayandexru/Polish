#ifndef __MOTOR_Z_H__
#define __MOTOR_Z_H__

#include "Defs.h"

#include "Motors.h"
#include "Timers.h"

extern volatile TIMER_CONTROL_STRUCT tcs_MotorZ; 	// структура управления таймером движения радиальным двигателем 
extern volatile TFMC 	mc_Z;
extern volatile TFMS 	ms_Z;

void	MotorZ_Handler(void);

#endif
//#ifndef __MOTOR_X_H__



