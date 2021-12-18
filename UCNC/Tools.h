
//****************************************************************************
//
//                            Инструменты
//
//****************************************************************************


#ifndef __TOOLS_H_
#define __TOOLS_H_
#include "Defs.h"

#define OUTF1T(a) (int)((a)*1000)
#define OUTF1H(a) (int)((a)*100)
#define OUTF1D(a) (int)((a)*10)
#define OUTF1(a) (int)(a)
#define LPMIN 1
// ограничения
//#define CLPON(T,LPOFF) ( T > (LPOFF+LPMIN) ? (T-LPOFF) : LPMIN)
//#define CLPOFF(T,LPON) ( T > (LPON+LPMIN) ? (T-LPON) : LPMIN)
// эксперименты
#define LPKORR 0
#define CLPOFF(T,LPON) ( T > (LPON+LPMIN+LPKORR) ? (T-LPON-LPKORR) : LPMIN)
//#define CHECKLPON(LPON) {if (LPON < LPMIN) LPON=LPMIN;}
#define CHECKLPOFF(LPOFF) {if (LPOFF < LPMIN) LPOFF=LPMIN;}
// эксперименты
//#define CLPONY(T,LPOFF) (1)
//#define CHECKLPON(LPON) (LPON)
// без ограничений

// Вычислить контрольную сумму CRC8
u8 CRC8(u8 *ptr, u8 crc, u16 len);

float sqr(float x);
int Round(float f);
s32 abss32(s32 a);

#endif // __TOOLS_H_

