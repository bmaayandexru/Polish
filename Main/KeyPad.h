#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "Defs.h"
// ���������� �� ������������� ������ �� RS-485
extern u8	*pUsesKP485;
// ����� ������
extern u8	*pAddrKPCtrl;

// �������� ��������� ������
// �������� ���� ��������
extern s16 *pDrDelay;
// ����� DoubleClick � 0,01 � 
extern s16 *pDCTime;
// ������� ���������� �������� (� ����� ��������? %/� ?)
extern s16 *pPercVmin;
// �������� ���������� ��������� -100 +100
#ifdef __SAW__
extern s16	*pRmove;
extern s16	*pVumove;
extern s16	*pAmove;
extern s16	*pVdmove;
#endif 
#ifdef __FREZER__
extern s16	*pYmove; 
extern s16	*pZmove;
extern s16	*pXmove;
extern s16	*pUnusedmove;
#endif 

// 5 ������ 0 100
extern s16 *pBtn5;
// ������������ ���� 0 ��� 100 �� ������ 6
extern s16 *pAxisSwitch;
// �������
extern s16 *pBUZZ;



void KPInit(void);
void KPQuery(void);
void KPAnswer(u8 * buffer,u16 len);

#endif
//#define __KEYPAD_H__

