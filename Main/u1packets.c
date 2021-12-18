#include "VirtualPins.h"
#include "UART.h"
#include "u1packets.h"
#include "modbus.h"
#include "queue.h"
#include "handlers.h"

void mbFrzPackHandler1(u8 * buffer,u16 len){
	WaitFlag = 1;
//	Msg("WaitFlag %d \r\n",WaitFlag);
	// зафиксировать буфер квитанции в очереди
	quFixAnswer(buffer,len);
}

u8 buffer1[255];

void	UART1_Thread(void){
	u16 Count;
	Count=UARTx_ReadyRecvData(1);
//	TITimer(tiTest2,tiMsToTick(1000), Msg("u"));
	if (Count) {
		//Msg("%d ",Count);
		// данные есть
//		if (UARTx_RecvBuffer(1,buffer1,Count)){
		if (UART1_RecvBuffer(buffer1,Count)){
			//Msg("%2X",buffer1[0]);
//			// принимаем и отправляем на обработку
			mbRecvBuffer(1,buffer1,Count);
		} 
	} else {
		mbIdle(1);
		WaitAndFreeUartLine();
	}
}




