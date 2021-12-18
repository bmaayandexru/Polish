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
// ���������� ���������� ��������� ���� ��� ��������

u16 UARTx_SendBuffer(u8 num,u8 * buffer,u16 buflen);
// �������� buffer �������� count
// ���������� ���������� ���������� ���������� ����
// �������������� ������������� ������������� ��������
// if (UART_PlaceForSend(0) >= count) UART_SendBuffer(0,buffer,count);

// �� �� ��� � UARTx_SendBuffer ������ �������
u16 UART0_SendBuffer(u8 * buffer,u16 buflen);
u16 UART1_SendBuffer(u8 * buffer,u16 buflen);


u16 UARTx_ReadyRecvData(u8 num);
// ���������� ���������� ���� ������� � ������

u16 UARTx_RecvBuffer(u8 num,u8 * buffer,u16 buflen);
// ��������� buflen ���� � buffer
// ���������� ���������� ���������� �������� ����
// �������������� �������������
// if (count=UART_ReadyRecvData(0)>0) UART_RecvBuffer(0,buffer,count);
// � ����� 
// if (count <= UART_ReadyRecvData(0)) UART_RecvBuffer(0,buffer,count);

// �� �� ����� ������ ������� ����������� ��� ������ ����
u16 UART0_RecvBuffer(u8 * buffer,u16 buflen);
u16 UART1_RecvBuffer(u8 * buffer,u16 buflen);


// ������� ���������� ��������� RE � DE ��� rs485. ������ ��� UART1 !!!!!!!
//void BusyUartLine(void);
// �������� ����� �� ��������
// �������� �� define
//#define DefBusyUartLine	{/*__nop(); __nop();*/ DE_PORT->FIOSET = (DE_PIN_MASK|RE_PIN_MASK);} 
#define DefBusyUartLine	DE_PORT->FIOSET = (DE_PIN_MASK|RE_PIN_MASK)


//void FreeUartLine(void);
// ����������� ����� (������������ �� ����)
// �������� �� define
//#define DefFreeUartLine	{/*__nop(); __nop();*/ DE_PORT->FIOCLR = (DE_PIN_MASK|RE_PIN_MASK);} 
#define DefFreeUartLine	DE_PORT->FIOCLR = (DE_PIN_MASK|RE_PIN_MASK)

void InitHalfDupControlSignal(void);
// ������������� �� �������������� ����� UART1

void InitHalfDupWaitInterval(u32 baud_rate);
// ������������� �������� ������������ ����� 
//(���������� � ���������� ����� �������� ���������� �������)
 
void StartDelay(void);
// ����� �������� ������������ ����� (���������� � ���������� �������� UART1)

void WaitAndFreeUartLine(void);
// �������� ��������� �������� � ������������ ����� (���������� � main())

void InitFullDupControlSignal(void);
// ������������� �� ��������������� �����


#endif
