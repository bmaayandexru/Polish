#include "Defs.h"
#include <stdio.h>
#include <string.h>
#include "msg.h"
#include "modbus.h" 
#include "regs.h"
#include "u0packets.h"
// для Msg()
#define MsgBufSize 200
u16 MsgLen = 0;
u8 MsgBuf[MsgBufSize];

char bufmsg[120];
va_list     vArgs;

void  Msg (const  u8 *format, ...)
{
//	char * pb;
	int len = 0;
//    va_list     vArgs;
	memset(bufmsg,0,120);
    va_start(vArgs, format);
    vsprintf(bufmsg, (char const *)format, vArgs);
    va_end(vArgs);
//	pb = buffer;
	//while (*pb++ != 0) len++;
	len = strlen(bufmsg);
	if ((len+MsgLen) < MsgBufSize) {
		memcpy(&(MsgBuf[MsgLen]),bufmsg,len);
		MsgLen+=len;
	}
}

void Dump(u8 * buffer,u16 count){
	u16 i;
	u8 * ptr;
	char dmp[100];
	u16 j = 0;
	for (i=0, ptr=buffer;i<count;i++) {
		j += sprintf(dmp+j,"%02X ",*ptr++);
	}
	Msg((const uint8_t *)dmp);
}

void	SMsg(void){

	if (MsgLen > 0) {
		mbByteToPack(0,ADDR_U0);
		mbByteToPack(0,cmDbgMsg);
		//Проверка максимального значения MsgLen
		if (MsgLen >= MsgBufSize) MsgLen = MsgBufSize-1; 
		mbBufferToPack(0,&(MsgBuf[0]), MsgLen);
		mbSendPack(0);
		MsgLen = 0;
	}
}
