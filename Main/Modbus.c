//#include <RTL.h>
#include <string.h>
#include "Defs.h"
#include "Modbus.h"
#include "ti.h"
#include "UART.h"
#include "queue.h"
#include "regs.h"
#include "msg.h"
#include "Nextion.h"

//u8 neEOLN[3]={0xFF,0xFF,0xFF};
										// все пакеты модбас теперь могут иметь такой 
										// конец для удобства обработки ПО
										// необходимость такого конца регулируется регистрами
										// названия уточняются

#define U0BBSIZE 256
// приемные буферы
u8 mbRBuffer0[8192];
u8 mbRBuffer1[256];

// счетчики принимаемых данных
u16 mbRDataLen0 = 0;
u16 mbRDataLen1 = 0;

// буферы для передачи
u8 mbSBuffer0[U0BBSIZE];
u8 mbSBuffer1[256];
// буферы для формирования пакетов
u8 mbSFBuf0[U0BBSIZE];
u8 mbSFBuf1[256];

volatile u8 WaitFlag = 0;

// счетчики данных для передачи
u16 mbSDataLen0 = 0;
u16 mbSDataLen1 = 0;
// счетчики для формирования команд
u16 mbSFDLen0 = 0;
u16 mbSFDLen1 = 0;

// указатели на обработчики пакетов
TPackHandler pPackHandler0 = 0;
TPackHandler pPackHandler1 = 0;

// задержки для скоростей 
u16 mbDelay0 = 305;//(3.5*1000000/(115200/10)) мкс;
//u16 mbDelay0 = 10000;//(3.5*1000000/(115200/10)) мкс;
//u16 mbDelay1 = 3646;//(3.5*1000000/(9600/10)) мкс;
u16 mbDelay1 = 3646;//(3.5*1000000/(9600/10)) мкс;
// расчет контрольной суммы для ModBus
u16 CRC16 (const u8 *nData, u16 wLength);

#define DELAY_SIZE_BY_CHAR 3.5
//#define DELAY_SIZE_BY_CHAR 4

void mbSetSpeed(u8 num,u32 sp){
	if (num == 0){
		mbDelay0 = (DELAY_SIZE_BY_CHAR*1000000/(sp/10));
		// ограничение из-за посчета времени
		// делаем так чтобы задержка была хотя бы 1 счет
		if (mbDelay0 < timerPeriod) mbDelay0 = timerPeriod;
	} else
	if (num == 1){
		mbDelay1 = (DELAY_SIZE_BY_CHAR*1000000/(sp/10));
//		Msg("DU1 %d ",mbDelay1);
	}
}

void mbSetHandler(u8 num,TPackHandler ph){
	if (num == 0){
		pPackHandler0 = ph;
	} else
	if (num == 1){
		pPackHandler1 = ph;
	}
}

u16 swap (u16 w){
	return ((w << 8) | (w >> 8));
}

BOOL mbCheckSum(u8 * buffer,u16 len){
	u16 rCRC;
// проверка контрольной суммы
	if (len < 4) return FALSE;
	else {
		memcpy((u8*)&rCRC,buffer+len-2,2);
		//rCRC = swap(rCRC);
		return (rCRC == CRC16(buffer,len-2));
	}
}

void mbRecvBuffer(u8 num, u8 * buffer,u16 len){
	if (num == 0) {
		memcpy(mbRBuffer0+mbRDataLen0,buffer,len);
		mbRDataLen0+=len;
		//Msg("%0X  %d",*buffer,mbRDataLen0);
		StartTime(timeWaitUART0);
	} else {
		memcpy(mbRBuffer1+mbRDataLen1,buffer,len);
		mbRDataLen1+=len;
		StartTime(timeWaitUART1);
	}
}

void mbIdle(u8 num) {
//	u16 rCRC;
	if (num == 0) {
		if (GetTime(timeWaitUART0) > tiMksToTick(mbDelay0)) {
			//Dump(mbRBuffer0,mbRDataLen0);
			//if (mbCheckSum(mbRBuffer0,mbRDataLen0)) {
			if (mbCheckSum(mbRBuffer0,mbRDataLen0-3)) { // -3 если FFFFFF
				// проверить контрольную сумму
				// выдать пакет	через обработчик
				//Dump(mbRBuffer0,mbRDataLen0);
				if (pPackHandler0) {
					(*pPackHandler0)(mbRBuffer0,mbRDataLen0);
				}
			}else{
				// пакет Nextion
				//nePack(mbRBuffer0,mbRDataLen0-3);
			}	
			// очистка буфера
			memset(mbRBuffer0,0,sizeof mbRBuffer0);
			mbRDataLen0 = 0;
			StopTime(timeWaitUART0);
		}
	} else {
		if (GetTime(timeWaitUART1) > tiMksToTick(mbDelay1)) {
			//Dump(mbRBuffer1,mbRDataLen1);
			if (mbCheckSum(mbRBuffer1,mbRDataLen1)) {
				if (pPackHandler1) {
					(*pPackHandler1)(mbRBuffer1,mbRDataLen1);
				}
			} else {
				// логирование ошибок контрольной суммы UART1
				if (*pErrCSU1) {
					Msg("Err CS U1 ");
					Dump(mbRBuffer1,mbRDataLen1);
					Msg("\r\n");
				}
			}
			// очистка буфера
			memset(mbRBuffer1,0,sizeof mbRBuffer1);
			mbRDataLen1 = 0;
			StopTime(timeWaitUART1);
		}
	}
}

void mbByteToPack(u8 num,u8 b){
	if (num == 0) {
		*(mbSFBuf0+mbSFDLen0)=b;
		mbSFDLen0++;
	} else 
	if (num == 1) {
		*(mbSFBuf1+mbSFDLen1)=b;
		mbSFDLen1++;
	}
}

void mbWordToPack(u8 num,u16 w){
	u16 tmpw;
	if (num == 0) {
		tmpw = swap(w);
		memcpy(mbSFBuf0+mbSFDLen0,&tmpw,2);
		mbSFDLen0 += 2;
	} else 
	if (num == 1) {
		tmpw = swap(w);
		memcpy(mbSFBuf1+mbSFDLen1,&tmpw,2);
		mbSFDLen1 += 2;
	}
}

void mbWordToPackNoSwap(u8 num,u16 w){
	u16 tmpw;
	if (num == 0) {
		tmpw = w;
		memcpy(mbSFBuf0+mbSFDLen0,&tmpw,2);
		mbSFDLen0 += 2;
	} else 
	if (num == 1) {
		tmpw = w;
		memcpy(mbSFBuf1+mbSFDLen1,&tmpw,2);
		mbSFDLen1 += 2;
	}
}

void mbBufferToPack (u8 num,u8 * buffer,u16 len){
	if (num == 0) {
		memcpy(mbSFBuf0+mbSFDLen0,buffer,len);
		mbSFDLen0 += len;
	} else 
	if (num == 1) {
		memcpy(mbSFBuf1+mbSFDLen1,buffer,len);
		mbSFDLen1 += len;
	}
}

void mbCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count){
	mbByteToPack(1,devaddr);
	mbByteToPack(1,cmd);
	mbWordToPack(1,regaddr);
	mbWordToPack(1,count);
	mbPackToQueue(quCmdNoTransit);
}

void mbInsCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count,u8 ofs){
	mbByteToPack(1,devaddr);
	mbByteToPack(1,cmd);
	mbWordToPack(1,regaddr);
	mbWordToPack(1,count);
	mbInsPackToQueue(quCmdNoTransit,ofs);
}

void mbSendPack(u8 num){
	u16 tmpw;
	if (num == 0) {
		tmpw = CRC16(mbSFBuf0,mbSFDLen0);
		mbWordToPackNoSwap(0,tmpw);
/*
		// добавить FFFFFF по регистру
		// а пока просто так
*/		
		mbBufferToPack(0,neEOLN,3);// Nextion EOLN FFFFFF
		//***
		memcpy(mbSBuffer0,mbSFBuf0,mbSFDLen0);
		mbSDataLen0 = mbSFDLen0;
/*
		если обмен только с Nextion обмен идет только с ней
		через модули Nextion
		передавать только если включен протокол
		if (*pCtrlModBus)
*/		
		if (1)
		UART0_SendBuffer(mbSBuffer0,mbSDataLen0);
		mbSDataLen0 = 0;
		mbSFDLen0 = 0;
	} else
	if (num == 1) {
		tmpw = CRC16(mbSFBuf1,mbSFDLen1);
		mbWordToPackNoSwap(1,tmpw);
		memcpy(mbSBuffer1,mbSFBuf1,mbSFDLen1);
		mbSDataLen1 = mbSFDLen1;
		UART1_SendBuffer(mbSBuffer1,mbSDataLen1);
		mbSDataLen1 = 0;
		mbSFDLen1 = 0;
	} 
}

void mbPackToQueue(u8 transit){
	quAddPack(mbSFBuf1,mbSFDLen1,transit);
	mbSFDLen1 = 0;
}

void mbInsPackToQueue(u8 transit,u8 ofs){
	quInsPack(mbSFBuf1,mbSFDLen1,transit,ofs);
	mbSFDLen1 = 0;
}

u16 CRC16 (const u8 *nData, u16 wLength)
{
static const u16 wCRCTable[] = {
0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

u8 nTemp;
u16 wCRCWord = 0xFFFF;

   while (wLength--)
   {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord ^= wCRCTable[nTemp];
   }
   return wCRCWord;
}

