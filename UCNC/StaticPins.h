#ifndef __STATIC_PINS_H__
#define __STATIC_PINS_H__

#include "Defs.h"
#include "LPC17xx.h"

// направление пинов в таблице aPin
#define DIR_OUT 	1
#define DIR_IN 		0
#define DIR_UNDEF 	0xFF

// количество ножек реально предназначенных для входа/выходы на плате (название платы UCNC Board 1.0)
#define PinCount 36 

// атрибуты пина
typedef struct {
	LPC_GPIO_TypeDef*	pPort;	// порт 
	u32					mPin;					// маска пина в порте
	u32					DIR;					// FF - не определено 0-выход 1-вход
//	u32 			trash;							// не используется, для выравнивания
} TPin;


// массив, описывающий выходы и входы платы UCNC 1.0
extern TPin aPin[];

#endif
