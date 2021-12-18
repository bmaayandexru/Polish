#ifndef __FREQCONV_H__
#define __FREQCONV_H__

#include "Defs.h"
// ������ ��� �� (MR0)
extern u32 * pFIPWM;
// ������������ ������� ��� ��� ��
extern u32 * pFIPWMFreq;

void FILoadConf(void);
void FIInit(void);
void FIUnlock(void);
void FISetFreq(u16 Freq);
void FISetDir(u8 rev);
void FIStart(void);
void FIStop(void);
void FIQuery(void);
void FIAnswer(u8 * buffer,u16 len);


#endif
