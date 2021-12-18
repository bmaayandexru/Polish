#include <string.h>
#include "Defs.h"
#include "KeyPad.h"
#include "modbus.h"
#include "queue.h"
// ОТЛАДКА УБРАТЬ !!!
#include "msg.h"

// разрешение на использование пульта по RS-485
u8	*pUsesKP485; 
// адрес пульта
u8	*pAddrKPCtrl; 

// регистры-отражения регистров частотника по порядку
// задержка анти дребезга
s16 *pDrDelay;
// время DoubleClick в 0,01 с 
s16 *pDCTime;
// процент увеличения скорости (в каких единицах? %/с ?)
s16 *pPercVmin;
// регистры управления движением -100 +100
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
// 5 кнопка 0 100
s16 *pBtn5;
// переключение осей 0 или 100 по кнопке 6
s16 *pAxisSwitch;
// пищалка
s16 *pBUZZ;


void KPInit(void){
	if (*pUsesKP485) {
		// установка адреса
	//	mbCmd485(0xAA,6,1212,*pAddrKPCtrl);
		// отключение 5-й лампы от кнопки
		mbCmd485(*pAddrKPCtrl,5,1111,0xFF00);
		// настроечные регистры пульта
		mbCmd485(*pAddrKPCtrl,6,1200,*pDrDelay); // задержка анти дребезга
		mbCmd485(*pAddrKPCtrl,6,1201,*pDCTime);  // время DoubleClick
		// установка порога	минимальной скорости
		mbCmd485(*pAddrKPCtrl,6,1202,*pPercVmin);
	}
}

void KPQuery(void){
	// добавляем в очередь опрос регистров пульта
	mbCmd485(*pAddrKPCtrl,3,1200,12);
}

void KPAnswer(u8 * buffer,u16 len){
	u16 Addr;
	u8 i;
	s16 wbuf[10];
//	Msg("kpA %d %d",*(buffer+1),*(buffer+2));
//	Dump(buffer,len);
	if ((*(buffer+1)==3)&&(*(buffer+2)>=20)){
		// это ответ на запрос с длиной больше либо равной 20
		// проверяем адрес по которому он выполнен
		memcpy(&Addr,&(qu.aqu[qu.head].buf[2]),2);
		Addr = swap(Addr);
		//Msg("Addr %d",Addr);
		if (Addr == 1200) {
			// наш адрес 
			// свопим массив
			memcpy((u8*)wbuf,(buffer+3),20);
			//Dump((u8*)wbuf,20);
			for (i=0;i<10;i++) {wbuf[i]=swap(wbuf[i]);}
			// отражаем в регистрах если разрешено
			//Msg("w3 %d w4 %d\r\n",wbuf[3],wbuf[4]);
			if (*pUsesKP485) {
				// здесь нужно поменять знак у wbuf[3,4] 
				wbuf[3] = - wbuf[3]; 	// pYMove
				wbuf[4] = - wbuf[4];	// pZMove
				wbuf[5] = - wbuf[5];	// pXMove
				// чтобы не переделывать прошивку пульта
				memcpy((u8*)pDrDelay,(u8*)wbuf,20);
			}
		}
	}
}
