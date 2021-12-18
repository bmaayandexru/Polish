#ifndef __MOTOR_VUD_H__
#define __MOTOR_VUD_H__

#include "Defs.h"

#ifdef __SAW__
#include "Motors.h"
#include "Timers.h"

extern TIMER_CONTROL_STRUCT tcs_MotorVu,tcs_MotorVd;
extern TMC 	mc_Vu,mc_Vd;
extern TMS 	ms_Vu,ms_Vd;

void	MotorVu_Handler(void);
void	MotorVd_Handler(void);

#endif
// #ifdef __SAW__
#endif
//#ifndef __MOTOR_VUD_H__
