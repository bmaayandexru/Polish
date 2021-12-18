#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "Defs.h"

// коды ошибок ModBus
// функция не поддерживается
#define MBE_FUNC_FAULT 1
// ошибка адреса
#define MBE_ADDR_FAULT 2
// ошибка данных
#define MBE_DATA_FAULT 3

// тип обработчика приема пакета
typedef void(*TPackHandler)(u8 * buffer,u16 len);

extern u8 mbFixBuf1[256];

extern volatile u8 WaitFlag;

// функции, обеспечивающие прием
void mbSetHandler(u8 num,TPackHandler ph);
// установка обработчика

void mbSetSpeed(u8 num,u32 sp);
// сообщаем протоколу скорость линии в бодах для вычисления интервала молчания

void mbRecvBuffer(u8 num, u8 * buffer,u16 len);
// прием буфера

void mbIdle(u8 num);
// фон (анализ времени от приема последнего байта и вызов обработчика)

// фунции обеспечивающие передачу																	 
void mbByteToPack(u8 num,u8 b);
// добавление байта в буфер пакета

void mbWordToPack(u8 num,u16 w);
// добавление слова в буфер пакета

void mbWordToPackNoSwap(u8 num,u16 w);
// добавление слова в буфер пакета без свапа

void mbBufferToPack (u8 num,u8 * buffer,u16 len);
// добавление буфера в буфера пакета

void mbSendPack(u8 num);
// подсчет контрольной суммы и передача пакета по UARTу

void mbPackToQueue(u8 transit); 
// постановка в очередь пакета UART1

void mbInsPackToQueue(u8 transit,u8 ofs);
// вставка в очередь пакета UART1

void mbCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count);
// команда постановки в очередь rs-485

void mbInsCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count,u8 ofs);
// команда вставки в очередь rs-485

u16 swap (u16 w);

#endif
