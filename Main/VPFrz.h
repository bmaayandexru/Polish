#ifndef __VPFRZ_H__
#define __VPFRZ_H__

#include "Defs.h"

#ifdef __FREZER__

#include "VirtualPins.h"
// фрезер
// выходы
#define MOTOR_X_STEP 	0
#define MOTOR_X_DIR		1
#define MOTOR_X_EN		2
#define MOTOR_Yl_STEP 	3
#define MOTOR_Yl_DIR	4
#define MOTOR_Yl_EN		5
#define MOTOR_Yr_STEP 	6
#define MOTOR_Yr_DIR	7
#define MOTOR_Yr_EN		8
#define MOTOR_Z_STEP 	9
#define MOTOR_Z_DIR		10
#define MOTOR_Z_EN		11

#define COOLER1		12
#define COOLER2		13

#define	SPINDEL_BACK	14
#define	SPINDEL_FORW	15

// IN1 20
#define BTN_MOTOR_Y_DIR		20
#define BTN_MOTOR_Y_BACK	21
#define BTN_MOTOR_Z_DIR		20
#define BTN_MOTOR_Z_BACK	21
#define BTN_MOTOR_X_DIR		22
#define BTN_MOTOR_X_BACK	23
#define BTN_NUM_5			24

#define BTN_AXIS_SWITCH		25
// IN7
#define SENS_HORIZONTAL_POINT 26
// IN8
#define SENS_SET_POINT		27
// IN9
#define SENS_MOTOR_Y		28
// IN10
#define SENS_MOTOR_Z		29
// IN11
#define SENS_MOTOR_X		30
#define CRUSH_WATER			32

extern TaVPIN vPinsdef;
#endif
//#ifdef __FREZER__

#endif
//#define __VPFRZ_H__
