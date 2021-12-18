#ifndef __MOTOR_Y_H__
#define __MOTOR_Y_H__

#include "Defs.h"

#include "Motors.h"
#include "Timers.h"

extern volatile TIMER_CONTROL_STRUCT tcs_MotorY; 	// структура управления таймером движения радиальным двигателем 
extern volatile TFMC 	mc_Y;
extern volatile TFMS 	ms_Y;

void	MotorY_Handler(void);

#endif
//#ifndef __MOTOR_Y_H__



