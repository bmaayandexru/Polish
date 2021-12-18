#ifndef __STATIC_PINS_H__
#define __STATIC_PINS_H__

#include "Defs.h"
#include "LPC17xx.h"

// ����������� ����� � ������� aPin
#define DIR_OUT 	1
#define DIR_IN 		0
#define DIR_UNDEF 	0xFF

// ���������� ����� ������� ��������������� ��� �����/������ �� ����� (�������� ����� UCNC Board 1.0)
#define PinCount 36 

// �������� ����
typedef struct {
	LPC_GPIO_TypeDef*	pPort;	// ���� 
	u32					mPin;					// ����� ���� � �����
	u32					DIR;					// FF - �� ���������� 0-����� 1-����
//	u32 			trash;							// �� ������������, ��� ������������
} TPin;


// ������, ����������� ������ � ����� ����� UCNC 1.0
extern TPin aPin[];

#endif
