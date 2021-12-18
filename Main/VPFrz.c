#include "Defs.h"

#ifdef __FREZER__

#include "VirtualPins.h"
#include "VPFrz.h"

// таблица виртуальных пинов по умолчанию

TaVPIN vPinsdef = {
//	nPin,	Inv,	State
	{OUT1,	1,		0},	// MOTOR_X_STEP
	{OUT2,	1,		0}, // MOTOR_X_DIR
	{OUT3,	1,		0}, // MOTOR_X_EN
	{OUT4,	1,		0}, // MOTOR_Yl_STEP
	{OUT5,	1,		0}, // MOTOR_Yl_DIR
	{OUT6,	1,		0}, // MOTOR_Yl_EN
	{OUT7,	1,		0}, // MOTOR_Yr_STEP
	{OUT8,	0,		0},	// MOTOR_Yr_DIR		
	{OUT9,	1,		0},	// MOTOR_Yr_EN
	{OUT10,	1,		0},	// MOTOR_Z_STEP
	{OUT11,	0,		0},	// MOTOR_Z_DIR
	{OUT12,	1,		0},	// MOTOR_Z_EN
	{OUT13,	1,		0},	// COOLER1
	{OUT14,	1,		0},	// COOLER2
	{OUT15,	0,		0},	// SPINDEL_F
	{OUT16,	0,		0},	// SPINDEL_B
	{OUT17,	1,		0},
	{OUT18,	1,		0},
	{OUT19,	1,		0},
	{OUT20,	1,		0},

	{IN1,	1,		0},	 // BTN_MOTOR_YZ_DIR
	{IN2,	1,		0},	 // BTN_MOTOR_YZ_BACK
	{IN3,	1,		0},	 // BTN_MOTOR_X_DIR
	{IN4,	1,		0},	 // BTN_MOTOR_X_BACK
	{IN5,	1,		0},	 // BTN_SET_POINT	BTN_SET_PAUSE
	{IN6,	1,		0},  //	BTN_LOW_SPEED  	BTN_SET_PAUSE_OFF_TROS
	{IN7,	1,		0},
	{IN8,	1,		0},
	{IN9,	1,		0},		 // SENS_MOTOR_Z
	{IN10,	1,		0},	 // SENS_MOTOR_Y
	{IN11,	1,		0},	 // SENS_MOTOR_X
	{IN12,	1,		0},	 // 
	{IN13,	1,		0},	 // CRASH_WATER
	{IN14,	1,		0},	 // 
	{IN15,	1,		0},	 // 
	{IN16,	1,		0}	 // 

	};

#endif
//#ifdef __FREZER__
