#include "Defs.h"
#include "modbus.h"
#include "VirtualPins.h"
#include "FreqInvr.h"
#include "regs.h"
#include "msg.h"
#include "pwm.h"

#ifdef __SAW__
#include "VPSaw.h"
#endif
#ifdef __FREZER__
#include "VPFrz.h"
#endif

s8	TROS_DIR;

u32 * pFIPWM;
// максимальная частота для ШИМ ЧП
u32 * pFIPWMFreq;

void FILoadConf(void){
}

void FIInit(void){

//	Msg("FIInit %d\r\n",*pFIType);
	TROS_DIR = 1;
	PWM_Init(*pFIPWM);
	if ((*pFIPWMFreq)==0) *pFIPWMFreq = 3000;
	// старт шима для 27 м/с
//	PWM_Set((u32)(611*((*pFIPWM)-1)/(*pFIPWMFreq)));
	// пытаемся отключить шпиндель фрезера при инициализации
	PWM_Set(0);
	PWM_Start();
	FIStop();
}

void FIUnlock(void){
//	Msg("FIUnlock %d\r\n",*pFIType);
}

void FISetFreq(u16 Freq){
	u32 F2;
	Freq*=10;
	if ((*pFIPWMFreq)==0) *pFIPWMFreq = 3000;
	if (Freq < (*pFIPWMFreq))  
	  F2=(u32)(Freq*((*pFIPWM)-1)/(*pFIPWMFreq));  
	else F2 = (*pFIPWM)-1;
	Msg("MR0 %d MR0Freq %d Freq %d F2 %d\r\n",*pFIPWM,*pFIPWMFreq,Freq,F2);
	PWM_Set(F2);
	PWM_Start();
}

void FISetDir(u8 rev){
//	Msg("FIDir %d %d\r\n",*pFIType,rev);
	if (rev) {
		TROS_DIR=0;
	} else {
		// прямое вращение
		TROS_DIR=1;
	}
}

void FIStart(void){
	FIStop();
	if (TROS_DIR)	QSetPin(SPINDEL_FORW);
	else			QSetPin(SPINDEL_BACK);
	PWM_Start();
}

void FIStop(void){
	QClrPin(SPINDEL_FORW);
	QClrPin(SPINDEL_BACK);
}

void FIQuery(void){
}

void FIAnswer(u8 * buffer,u16 len){
}
