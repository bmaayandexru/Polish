#ifndef __NEXTION_H__
#define __NEXTION_H__

#include "Defs.h"

/*
// коды возврата nextion
// 0x00 не верная инструкция
#define NER_InstFault 0x00

// инструкция выполнена верно
#define NER_InstOk		0x01

// неверный идентификатор компонета
#define NER_IDFault		0x02

// не верный идентификатор страницы
#define NER_PagIDFault	0x03

// не верный индентификатор изображения
#define NER_PicIDFault	0x04

// не верный идетификатор изображения
#define NER_
// 
#define NER_
// 
#define NER_
// 
#define NER_
// 
#define NER_
// 
#define NER_
// 
#define NER_
// 
#define NER_

// тип обработчика приема пакета
typedef void(*TPackHandler)(u8 * buffer,u16 len);


// функции, обеспечивающие прием
void neSetHandler(u8 num,TPackHandler ph);
// установка обработчика

void neRecvBuffer(u8 num, u8 * buffer,u16 len);
// прием буфера

void neIdle(u8 num);
// фон (анализ времени от приема последнего байта и вызов обработчика)

// передача строчной команды типа "sendme"
void neCmd(u8 * cmd);

// передача строчной команды с числовым параметром типа "n0.val" "=" 100
void neCmdVal(u8 * cmd,s32 val);

// передача строчной команды со строчных значением параметром типа "n0.val" "=" 100
void neCmdVal(u8 * cmd,u8 val);

//
// передача запроса типа get с указание что ждем и сколько (уточняется)
void neCmdQwr(u8 * cmd,u8 WhatWait,u8 WaitCount);

// остальные в резерве
void mbByteToPack(u8 num,u8 b);
// добавление байта в буфер пакета

void mbWordToPack(u8 num,u16 w);
// добавление слова в буфер пакета

void mbWordToPackNoSwap(u8 num,u16 w);
// добавление слова в буфер пакета без свапа

void mbBufferToPack (u8 num,u8 * buffer,u16 len);
// добавление буфера в буфера пакета

void mbSendPack(u8 num);
// передача пакета по UARTу


*/
#endif
