#include <string.h>
#include "Defs.h"
#include "KeyPad.h"
#include "modbus.h"
#include "queue.h"
// ������� ������ !!!
#include "msg.h"

// ���������� �� ������������� ������ �� RS-485
u8	*pUsesKP485; 
// ����� ������
u8	*pAddrKPCtrl; 

// ��������-��������� ��������� ���������� �� �������
// �������� ���� ��������
s16 *pDrDelay;
// ����� DoubleClick � 0,01 � 
s16 *pDCTime;
// ������� ���������� �������� (� ����� ��������? %/� ?)
s16 *pPercVmin;
// �������� ���������� ��������� -100 +100
#ifdef __SAW__
s16	*pRmove;
s16	*pVumove;
s16	*pAmove;
s16	*pVdmove;
#endif 
#ifdef __FREZER__
s16	*pYmove; 
s16	*pZmove;
s16	*pXmove;
s16	*pUnusedmove;
#endif 
// 5 ������ 0 100
s16 *pBtn5;
// ������������ ���� 0 ��� 100 �� ������ 6
s16 *pAxisSwitch;
// �������
s16 *pBUZZ;


void KPInit(void){
	if (*pUsesKP485) {
		// ��������� ������
	//	mbCmd485(0xAA,6,1212,*pAddrKPCtrl);
		// ���������� 5-� ����� �� ������
		mbCmd485(*pAddrKPCtrl,5,1111,0xFF00);
		// ����������� �������� ������
		mbCmd485(*pAddrKPCtrl,6,1200,*pDrDelay); // �������� ���� ��������
		mbCmd485(*pAddrKPCtrl,6,1201,*pDCTime);  // ����� DoubleClick
		// ��������� ������	����������� ��������
		mbCmd485(*pAddrKPCtrl,6,1202,*pPercVmin);
	}
}

void KPQuery(void){
	// ��������� � ������� ����� ��������� ������
	mbCmd485(*pAddrKPCtrl,3,1200,12);
}

void KPAnswer(u8 * buffer,u16 len){
	u16 Addr;
	u8 i;
	s16 wbuf[10];
//	Msg("kpA %d %d",*(buffer+1),*(buffer+2));
//	Dump(buffer,len);
	if ((*(buffer+1)==3)&&(*(buffer+2)>=20)){
		// ��� ����� �� ������ � ������ ������ ���� ������ 20
		// ��������� ����� �� �������� �� ��������
		memcpy(&Addr,&(qu.aqu[qu.head].buf[2]),2);
		Addr = swap(Addr);
		//Msg("Addr %d",Addr);
		if (Addr == 1200) {
			// ��� ����� 
			// ������ ������
			memcpy((u8*)wbuf,(buffer+3),20);
			//Dump((u8*)wbuf,20);
			for (i=0;i<10;i++) {wbuf[i]=swap(wbuf[i]);}
			// �������� � ��������� ���� ���������
			//Msg("w3 %d w4 %d\r\n",wbuf[3],wbuf[4]);
			if (*pUsesKP485) {
				// ����� ����� �������� ���� � wbuf[3,4] 
				wbuf[3] = - wbuf[3]; 	// pYMove
				wbuf[4] = - wbuf[4];	// pZMove
				wbuf[5] = - wbuf[5];	// pXMove
				// ����� �� ������������ �������� ������
				memcpy((u8*)pDrDelay,(u8*)wbuf,20);
			}
		}
	}
}
