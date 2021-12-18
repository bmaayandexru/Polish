#ifndef __NEXTION_H__
#define __NEXTION_H__

#include "Defs.h"

/*
// ���� �������� nextion
// 0x00 �� ������ ����������
#define NER_InstFault 0x00

// ���������� ��������� �����
#define NER_InstOk		0x01

// �������� ������������� ���������
#define NER_IDFault		0x02

// �� ������ ������������� ��������
#define NER_PagIDFault	0x03

// �� ������ �������������� �����������
#define NER_PicIDFault	0x04

// �� ������ ������������ �����������
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

// ��� ����������� ������ ������
typedef void(*TPackHandler)(u8 * buffer,u16 len);


// �������, �������������� �����
void neSetHandler(u8 num,TPackHandler ph);
// ��������� �����������

void neRecvBuffer(u8 num, u8 * buffer,u16 len);
// ����� ������

void neIdle(u8 num);
// ��� (������ ������� �� ������ ���������� ����� � ����� �����������)

// �������� �������� ������� ���� "sendme"
void neCmd(u8 * cmd);

// �������� �������� ������� � �������� ���������� ���� "n0.val" "=" 100
void neCmdVal(u8 * cmd,s32 val);

// �������� �������� ������� �� �������� ��������� ���������� ���� "n0.val" "=" 100
void neCmdVal(u8 * cmd,u8 val);

//
// �������� ������� ���� get � �������� ��� ���� � ������� (����������)
void neCmdQwr(u8 * cmd,u8 WhatWait,u8 WaitCount);

// ��������� � �������
void mbByteToPack(u8 num,u8 b);
// ���������� ����� � ����� ������

void mbWordToPack(u8 num,u16 w);
// ���������� ����� � ����� ������

void mbWordToPackNoSwap(u8 num,u16 w);
// ���������� ����� � ����� ������ ��� �����

void mbBufferToPack (u8 num,u8 * buffer,u16 len);
// ���������� ������ � ������ ������

void mbSendPack(u8 num);
// �������� ������ �� UART�


*/
#endif
