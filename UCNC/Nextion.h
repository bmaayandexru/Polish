#ifndef __NEXTION_H__
#define __NEXTION_H__

#include "Defs.h"

//--------------------- ���� �������� nextion -----------------------------
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

// �� ������ ������������ ������
#define NER_FntIDFault	0x05

// ������������ �������� ��������
#define NER_FopFault 	0x06

// �������� CRC
#define NER_CRCFault	0x09

// �������� ��������� �������� �������� 
#define NER_BaudFaul	0x11

// �������� ������������� waveform ��� ������ ������
#define NER_WavIDFault	0x12

// ������������ ��� ���������� ��� �������
#define NER_NameFault	0x1A

// ������������ �������� � ����������
#define NER_VOPFault	0x1B

// �� ������� ��������� ����������
#define NER_OPFault	0x1C

//���� �������� EEPROM
#define NER_EEPROMFault 0x1D

// ������������ ���������� ����������
#define NER_PCFault	0x1E

// ���� �������� �����-������
#define NER_IOFailt	0x1F

// ������������ Escape-������
#define NER_EscFault	0x20

// ������� ������� ��� ����������
#define NER_LongName	0x23

// ������������ ����������������� ������
#define NER_UARTFull	0x24

// ������� ������� (����������)
#define NER_PushEvent	0x65

// ������� ����� ��������
#define NER_CurPage	0x66

// ���������� ������� (�����������)
#define NER_PushKoodWake	0x67

// ���������� ������� (������ �����)
#define NER_PushKoodSleep	0x68

// �������� ������
#define NER_GetString	0x70

// �������� ������
#define NER_GetNum	0x71

// ������� � ������ �����
#define NER_ToSleep	0x86

// �������������� ����������� �� ���
#define NER_AutoWake	0x87

// ����������
#define NER_Ready	0x88

// ������ ���������� � microSD
#define NER_StartUpdateMSD	0x89

// �������� ������ ���������
#define NER_TramsDataEnd	0xFD

// ���������� � ��������� ������
#define NER_RecvDataReady	0xFE

extern u8 neEOLN[]; // ������ ����� FFFFFF
										// ������������ � Modbus
										// ��� ������ ������ ������ ����� ����� ����� 
										// ����� ��� �������� ��������� ��
										// ������������� ������ ����� ������������ ����������
										// �������� ����������

//------------------- �������, �������������� ����� ------------------------

// ��� ����������� ������ ������
typedef void(*TPackHandler)(u8 * buffer,u16 len);

// ��������� �����������
void neSetHandler(u8 num,TPackHandler ph);

// ����� ������
void neRecvBuffer(u8 num, u8 * buffer,u16 len);

// �������� �������� ������� ���� "sendme"
void neCmd(u8 * cmd);

// �������� �������� ������� � �������� ���������� ���� "n0.val" "=" 100
void neCmdVal(u8 * cmd,s32 val);

// �������� ������� ���� get � �������� ��� ���� � ������� (����������)
void neCmdQwr(u8 * cmd,u8 WhatWait,u8 WaitCount);



#endif
