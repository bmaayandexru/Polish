#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "Defs.h"
// разрешение на использование пульта по RS-485
extern u8	*pUsesKP485;
// адрес пульта
extern u8	*pAddrKPCtrl;

// регистры отражения пульта
// задержка анти дребезга
extern s16 *pDrDelay;
// время DoubleClick в 0,01 с 
extern s16 *pDCTime;
// процент увеличения скорости (в каких единицах? %/с ?)
extern s16 *pPercVmin;
// регистры управления движением -100 +100
#ifdef __SAW__
extern s16	*pRmove;
extern s16	*pVumove;
extern s16	*pAmove;
extern s16	*pVdmove;
#endif 
#ifdef __FREZER__
extern s16	*pYmove; 
extern s16	*pZmove;
extern s16	*pXmove;
extern s16	*pUnusedmove;
#endif 

// 5 кнопка 0 100
extern s16 *pBtn5;
// переключение осей 0 или 100 по кнопке 6
extern s16 *pAxisSwitch;
// пищалка
extern s16 *pBUZZ;



void KPInit(void);
void KPQuery(void);
void KPAnswer(u8 * buffer,u16 len);

#endif
//#define __KEYPAD_H__

