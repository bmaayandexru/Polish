#include "Defs.h"

#ifdef __SAW__

#include "VirtualPins.h"
#include "VPSaw.h"


// таблица виртуальных пинов по умолчанию
TaVPIN vPinsdef = {
//	nPin,	Inv,	State
	{OUT1,	1,		0},	// MOTOR_R_STEP
	{OUT2,	1,		0}, // MOTOR_R_DIR
	{OUT3,	1,		0}, // MOTOR_R_EN
	{OUT4,	1,		0}, // MOTOR_A_STEP
	{OUT5,	1,		0}, // MOTOR_A_DIR
	{OUT6,	1,		0}, // MOTOR_A_EN
	{OUT7,	1,		0}, // MOTOR_Vu_STEP
	{OUT8,	0,		0},	// MOTOR_Vu_DIR		
	{OUT9,	1,		0},	// MOTOR_Vu_EN
	{OUT10,	1,		0},	// MOTOR_Vd_STEP
	{OUT11,	1,		0},	// MOTOR_Vd_DIR
	{OUT12,	1,		0},	// MOTOR_Vd_EN
	{OUT13,	1,		0},
	{OUT14,	1,		0},
	{OUT15,	1,		0},
	{OUT16,	1,		0},	// TROS_START
	{OUT17,	1,		0},
	{OUT18,	1,		0},
	{OUT19,	1,		0},
	{OUT20,	1,		0},

	{IN1,	1,		0},	 // BTN_MOTOR_R_DIR
	{IN2,	1,		0},	 // BTN_MOTOR_R_BACK
	{IN3,	1,		0},	 // BTN_MOTOR_A_DIR
	{IN4,	1,		0},	 // BTN_MOTOR_A_BACK
	{IN5,	1,		0},	 // BTN_SET_POINT	BTN_SET_PAUSE
	{IN6,	1,		0},  //	BTN_LOW_SPEED  	BTN_SET_PAUSE_OFF_TROS
	{IN7,	1,		0},
	{IN8,	1,		0},
	{IN9,	1,		0},
	{IN10,	1,		0},	 // SENS_MOTOR_A
	{IN11,	1,		0},	 // SENS_MOTOR_R
	{IN12,	1,		0},	 // SENS_MOTOR_Vu
	{IN13,	1,		0},	 // CRASH_WATER
	{IN14,	1,		0},	 // SENS_MOTOR_Vd
	{IN15,	1,		0},	 // CRUSH_POWER
	{IN16,	1,		0}	 // CRUSH_TROS

	};

#endif
