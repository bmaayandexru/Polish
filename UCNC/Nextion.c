#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "Defs.h"
#include "Nextion.h"
#include "UART.h"

u8 neEOLN[3]={0xFF,0xFF,0xFF};
u8 sbuf[100];	// ����� ��� �����
u8 len;			// ����� ������

//------------------- �������, �������������� ����� ------------------------

// ��� ����������� ������ ������
typedef void(*TPackHandler)(u8 * buffer,u16 len);


// ��������� �����������
void neSetHandler(u8 num,TPackHandler ph){
}

// ����� ������
void neRecvBuffer(u8 num, u8 * buffer,u16 len){
}	

// �������� �������� ������� ���� "sendme"
void neCmd(u8 * cmd){
	len = strlen((char*)cmd); 					// ���������� ����� ������
	memset(sbuf,0,255);										// ������� �����
	memcpy(sbuf,cmd,len);									// �������� ������
	memcpy((void*)(sbuf+len),neEOLN,3); 	// ���������� FFFFFF
	UART0_SendBuffer(sbuf,len+3);					// ���������� �����
}	

// �������� �������� ������� � �������� ���������� ���� "n0.val" "=" 100
void neCmdVal(u8 * cmd,s32 val){
}	

// �������� ������� ���� get � �������� ��� ���� � ������� (����������)
void neCmdQwr(u8 * cmd,u8 WhatWait,u8 WaitCount);
