#ifndef __VPSAW_H__
#define __VPSAW_H__

#include "Defs.h"

#ifdef __SAW__

#include "VirtualPins.h"

// смещение в таблице vPins
// сигналы управления радиальным двигателем
#define MOTOR_R_STEP 	0
#define MOTOR_R_DIR		1
#define MOTOR_R_EN		2

// сигналы управления угловым двигателем
#define MOTOR_A_STEP 	3
#define MOTOR_A_DIR		4
#define MOTOR_A_EN		5

// сигналы управления двигателем верхнего ролика
#define MOTOR_Vu_STEP 	6
#define MOTOR_Vu_DIR	7
#define MOTOR_Vu_EN		8

// сигналы управления двигателем нижнего ролика
#define MOTOR_Vd_STEP 	9
#define MOTOR_Vd_DIR	10
#define MOTOR_Vd_EN		11

// тестирование частоты main
#define TEST_FREQ_MAIN	12
// пуск/стоп троса 
#define TROS_START		15 	
//
#define ON_POWER_PRESS	17
#define ON_TABLE	18
#define ON_TROS		19

// кнопки управления направлением радиального двигателя
#define BTN_MOTOR_R_BACK	20
#define BTN_MOTOR_R_DIR		21

// направления радиального двигателя
#define BTN_MOTOR_A_DIR		22
#define BTN_MOTOR_A_BACK 	23

#define BTN_NUM_5			24
#define BTN_SET_POINT		24
#define BTN_LUFT			24
#define BTN_SET_PAUSE		24
#define BTN_SET_PAUSE_OFF_TROS	25
#define BTN_LOW_SPEED		25
#define BTN_AXIS_SWITCH		25

#define SWITCH_TROS		26
#define SWITCH_TABLE	27

//#define CRUSH_PRESS_TROS	28

#define SENS_MOTOR_A		29
#define SENS_MOTOR_R		30
#define SENS_MOTOR_Vu		31
//************				
#define CRUSH_WATER			32
//************
#define SENS_MOTOR_Vd		33

//#define CRUSH_PRESS_TABLE 		34
#define CRUSH_TROS 			35

extern TaVPIN vPinsdef;

#endif
//#ifdef __SAW__

#endif
//#ifdef __VPSAW_H__
