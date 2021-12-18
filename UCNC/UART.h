#ifndef __UART_H__
#define __UART_H__
#include "Defs.h"
#include "lpc17xx_uart.h"

typedef enum {FULL_DUPLEX = (0), HALF_DUPLEX} UART_DUPLEX_Type;

BOOL UARTx_Init(u8 num, 
				UART_DUPLEX_Type dup,
				u32 baud_rate,
 				UART_PARITY_Type par,
				UART_DATABIT_Type dbits,
				UART_STOPBIT_Type Stopbits);

u16 UARTx_PlaceForSend(u8 num);
// возвращает количество свободных байт для передачи

u16 UARTx_SendBuffer(u8 num,u8 * buffer,u16 buflen);
// передает buffer размером count
// возвращает количество фактически переданных байт
// предполагаемое использование вышеуказанных процедур
// if (UART_PlaceForSend(0) >= count) UART_SendBuffer(0,buffer,count);

// то же что и UARTx_SendBuffer только быстрее
u16 UART0_SendBuffer(u8 * buffer,u16 buflen);
u16 UART1_SendBuffer(u8 * buffer,u16 buflen);


u16 UARTx_ReadyRecvData(u8 num);
// возвращает количество байт готовых к приему

u16 UARTx_RecvBuffer(u8 num,u8 * buffer,u16 buflen);
// принимает buflen байт в buffer
// возвращает количество фактически принятых байт
// предполагаемое использование
// if (count=UART_ReadyRecvData(0)>0) UART_RecvBuffer(0,buffer,count);
// а также 
// if (count <= UART_ReadyRecvData(0)) UART_RecvBuffer(0,buffer,count);

// то же самое только быстрее персонально под каждый порт
u16 UART0_RecvBuffer(u8 * buffer,u16 buflen);
u16 UART1_RecvBuffer(u8 * buffer,u16 buflen);


// функции управления сигналами RE и DE для rs485. Только для UART1 !!!!!!!
//void BusyUartLine(void);
// занимаем линию на передачу
// заменяем на define
//#define DefBusyUartLine	{/*__nop(); __nop();*/ DE_PORT->FIOSET = (DE_PIN_MASK|RE_PIN_MASK);} 
#define DefBusyUartLine	DE_PORT->FIOSET = (DE_PIN_MASK|RE_PIN_MASK)


//void FreeUartLine(void);
// освобождаем линию (переключение на приём)
// заменяем на define
//#define DefFreeUartLine	{/*__nop(); __nop();*/ DE_PORT->FIOCLR = (DE_PIN_MASK|RE_PIN_MASK);} 
#define DefFreeUartLine	DE_PORT->FIOCLR = (DE_PIN_MASK|RE_PIN_MASK)

void InitHalfDupControlSignal(void);
// инициализация на полудуплексный режим UART1

void InitHalfDupWaitInterval(u32 baud_rate);
// инициализация задержки освобождения линии 
//(вызывается в прерывании после передачи последнего символа)
 
void StartDelay(void);
// старт задержки освобождения линии (вызывается в прерывании передачи UART1)

void WaitAndFreeUartLine(void);
// проверка окончания задержки и освобождение линии (вызывается в main())

void InitFullDupControlSignal(void);
// инициализация на полнодуплексный режим


#endif
