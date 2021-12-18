#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "Defs.h"
#include "Nextion.h"
#include "UART.h"

u8 neEOLN[3]={0xFF,0xFF,0xFF};
u8 sbuf[100];	// буфер под пакет
u8 len;			// длина данных

//------------------- функции, обеспечивающие прием ------------------------

// тип обработчика приема пакета
typedef void(*TPackHandler)(u8 * buffer,u16 len);


// установка обработчика
void neSetHandler(u8 num,TPackHandler ph){
}

// прием буфера
void neRecvBuffer(u8 num, u8 * buffer,u16 len){
}	

// передача строчной команды типа "sendme"
void neCmd(u8 * cmd){
	len = strlen((char*)cmd); 					// определ€ем дл€ну строки
	memset(sbuf,0,255);										// очищаем буфер
	memcpy(sbuf,cmd,len);									// копируем данные
	memcpy((void*)(sbuf+len),neEOLN,3); 	// добавлл€ем FFFFFF
	UART0_SendBuffer(sbuf,len+3);					// отправл€ем пакет
}	

// передача строчной команды с числовым параметром типа "n0.val" "=" 100
void neCmdVal(u8 * cmd,s32 val){
}	

// передача запроса типа get с указание что ждем и сколько (уточн€етс€)
void neCmdQwr(u8 * cmd,u8 WhatWait,u8 WaitCount);
