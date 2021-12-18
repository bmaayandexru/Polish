#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "Defs.h"

// ���� ������ ModBus
// ������� �� ��������������
#define MBE_FUNC_FAULT 1
// ������ ������
#define MBE_ADDR_FAULT 2
// ������ ������
#define MBE_DATA_FAULT 3

// ��� ����������� ������ ������
typedef void(*TPackHandler)(u8 * buffer,u16 len);

extern u8 mbFixBuf1[256];

extern volatile u8 WaitFlag;

// �������, �������������� �����
void mbSetHandler(u8 num,TPackHandler ph);
// ��������� �����������

void mbSetSpeed(u8 num,u32 sp);
// �������� ��������� �������� ����� � ����� ��� ���������� ��������� ��������

void mbRecvBuffer(u8 num, u8 * buffer,u16 len);
// ����� ������

void mbIdle(u8 num);
// ��� (������ ������� �� ������ ���������� ����� � ����� �����������)

// ������ �������������� ��������																	 
void mbByteToPack(u8 num,u8 b);
// ���������� ����� � ����� ������

void mbWordToPack(u8 num,u16 w);
// ���������� ����� � ����� ������

void mbWordToPackNoSwap(u8 num,u16 w);
// ���������� ����� � ����� ������ ��� �����

void mbBufferToPack (u8 num,u8 * buffer,u16 len);
// ���������� ������ � ������ ������

void mbSendPack(u8 num);
// ������� ����������� ����� � �������� ������ �� UART�

void mbPackToQueue(u8 transit); 
// ���������� � ������� ������ UART1

void mbInsPackToQueue(u8 transit,u8 ofs);
// ������� � ������� ������ UART1

void mbCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count);
// ������� ���������� � ������� rs-485

void mbInsCmd485(u8 devaddr,u8 cmd,u16 regaddr,u16 count,u8 ofs);
// ������� ������� � ������� rs-485

u16 swap (u16 w);

#endif
