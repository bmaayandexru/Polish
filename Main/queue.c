#include <string.h>
#include "queue.h"
#include "regs.h"
#include "ti.h"
#include "modbus.h"
#include "msg.h"
#include "FreqInvr.h"
#include "KeyPad.h"
#include "u0packets.h"


TQueue qu; // очередь

u8	EAddr = 0;
u8	ECmd = 0;
u8	ECode = 0;

void InitQueue(void){
	// инициализация очереди
	memset((void*)&qu,0,sizeof qu);
}

void ProcessingAnswer(void){
// обработка квитанции
	u8 Addr,Cmd;
	//Msg("RS485ProcAnswerOk\r\n");
	if (qu.aqu[qu.head].transit) {
		// ответ на запрос транзитных данных по UART1
		mbByteToPack(0,ADDR_U0);
		mbByteToPack(0,cmDataToU1);
		mbBufferToPack(0,qu.aqu[qu.head].qbuf,qu.aqu[qu.head].qlen);
		mbSendPack(0);
	}

	if ((*(qu.aqu[qu.head].qbuf+1)&0x80)==0x80) {
		EAddr = *(qu.aqu[qu.head].qbuf);
		ECmd = *(qu.aqu[qu.head].qbuf+1);
		ECode = *(qu.aqu[qu.head].qbuf+2);
		// регистрация в зависимости от состояния настроечных регистров
		if (*pAECmdDump) {
			Msg("CmdErr ");
			Dump(qu.aqu[qu.head].buf,qu.aqu[qu.head].len);
			Msg("\r\n");
		}
		if (*pAEMsg) {
			Msg("Answer Error. Addr %2X, Cmd  %2X, Code %2X.\r\n",EAddr,ECmd,ECode);
		}
		if (*pAEAnswDump) {
			Msg("AnswErr ");
			Dump(qu.aqu[qu.head].qbuf,qu.aqu[qu.head].qlen);
			Msg("\r\n");
		}
		if (EAddr == (*pAddrKPCtrl)) {
			if (*pKP_NA_Max) {
				if ((*pKP_NA_Max) < KP_NA_Count) {
					Msg("КР Error. \r\n");
					// сброс регистров в 0
					memset((u8*)pYmove,0,14);
				} else {
					KP_NA_Count++;
				}
			}
		}
	} else {
		// логирование правильно полученных квитанций
		Addr = *(qu.aqu[qu.head].qbuf);
		Cmd = *(qu.aqu[qu.head].qbuf+1);
		// сброс аварийных счетчиков
		if (Addr == (*pAddrKPCtrl)) { KP_NA_Count=0; *pLinkKP = 1;}

		if (*pACmdDump) {
			Msg("CmdOk ");
			Dump(qu.aqu[qu.head].buf,qu.aqu[qu.head].len);
			Msg("\r\n");
		}
		if (*pAMsg) {
			Msg("Answer Ok. Addr %2X, Cmd  %2X.\r\n",Addr,Cmd);
		}
		if (*pAAnswDump) {
			Msg("AnswOk ");
			Dump(qu.aqu[qu.head].qbuf,qu.aqu[qu.head].qlen);
			Msg("\r\n");
		}
		// проверка адреса
		if (*(qu.aqu[qu.head].qbuf) == *pAddrKPCtrl) {
			// квитанция пульта
			KPAnswer(qu.aqu[qu.head].qbuf,qu.aqu[qu.head].qlen);
		} else {
				Msg("Unknown device answer (%X).\r\n",*(qu.aqu[qu.head].qbuf));
				Dump(qu.aqu[qu.head].qbuf,qu.aqu[qu.head].qlen);
		}
	}
}	

void ProcessingNoAnswer(void){
// обработка отсутствия квитанции
	u8 Addr,Cmd;
	//Msg("485 NoAnsw");

	Addr = *(qu.aqu[qu.head].buf);
	Cmd = *(qu.aqu[qu.head].buf+1);
	
	if (*pANCmdDump) {
		Msg("CmdNA ");
		Dump(qu.aqu[qu.head].buf,qu.aqu[qu.head].len);
		Msg("\r\n");
	}
	if (*pANMsg) {
		Msg("No Answer. Addr %2X, Cmd  %2X.\r\n",Addr,Cmd);
	}
	
	if (qu.aqu[qu.head].repcount) qu.aqu[qu.head].repcount--;
	if (Addr == (*pAddrKPCtrl)) {
		if (*pKP_NA_Max) {
			if ((*pKP_NA_Max) < KP_NA_Count) {
//				Msg("КР silent. \r\n");
				*pLinkKP = 0;
				KP_NA_Count = 0;
				// сброс регистров в 0
				memset((u8*)pYmove,0,14);
			} else {
				KP_NA_Count++;
			}
		}
	}
}

void DeleteCurrentItem(){
// удаляем запись из очереди
	//memset((void*)&(qu.aqu[qu.head]),0,sizeof qu.aqu[qu.head]);
	//Msg("del h %d \r\n",qu.head);
	qu.head++;	// сдвигаем указатель на следующий элемент
	qu.head %= quMaxItemCount; // закольцовываем список
	//Msg("h %d \r\n",qu.head);
}


void QueueProcessing(void){
// обработка очереди
	if (!EndTI(tiQTest)) return;
//	Msg("QP");
//	StartTI(tiQTest,tiMsToTick(1000));
//	return;
	switch (qu.stage) {
		case 0: // готовность к передаче очередного пакета
//			Msg("PC %d ",quPackCount());
			if (quPackCount()) {
				// запускам таймаут
				StartTI(tiQueue,tiMsToTick(qu.aqu[qu.head].timeout));
				WaitFlag = 0; // сбрасываем флаг ожидания
				// передаем пакет
				mbBufferToPack(1,qu.aqu[qu.head].buf,qu.aqu[qu.head].len);
				mbSendPack(1);

//				// так не должно быть ПРОБА!!!
//				// но работает поэтому оставляем
				StartTI(tiLensSmdWait,tiMsToTick(10));
				while (!EndTI(tiLensSmdWait)) ;
//				Msg("s0 to %d len %d ",qu.aqu[qu.head].timeout,qu.aqu[qu.head].len);

				// переходим на стадию ожидания квитанции
				qu.stage = 1;
//				Msg("h %d ",qu.head);
				StartTI(tiQTest,tiMsToTick(40));
				// отладка 
//				StartTI(tiQTest,tiMsToTick(100));
			} else {
				StartTI(tiQTest,tiMsToTick(5));
				// отладка 
//				StartTI(tiQTest,tiMsToTick(100));
			}
			break;
		case 1: // ожидание квитанции на переданный пакет
			StartTI(tiQTest,tiMsToTick(5));
			// отладка 
			//StartTI(tiQTest,tiMsToTick(100));
			if (WaitFlag) {
//				Msg("WF %d\r\n",WaitFlag);
				qu.stage = 2;
				ProcessingAnswer();
				// удаляем запись из очереди
				DeleteCurrentItem();
				// передаем следующий пакет
				qu.stage = 0; 
			}
			else {
				if (EndTI(tiQueue)) {
					//Msg("rc %d\r\n",qu.aqu[qu.head].repcount);
					ProcessingNoAnswer();
					// проверяем на истечение повторов
					if (qu.aqu[qu.head].repcount==0) {
						// удаляем запись из очереди
						DeleteCurrentItem();
					}
					// передаем следующий пакет или текущий, если он не удален
					qu.stage = 0; 
				}
			}
			break;
/*
		case 2: // есть квитанция. обрабатываем
			ProcessingAnswer();
			// удаляем запись из очереди
			DeleteCurrentItem();
			// передаем следующий пакет
			qu.stage = 0; 
			break;
		case 3: // нет квитанции. обрабатываем
			ProcessingNoAnswer();
			// проверяем на истечение повторов
			if (qu.aqu[qu.head].repcount==0) {
				// удаляем запись из очереди
				DeleteCurrentItem();
			}
			// передаем следующий пакет или текущий, если он не удален
			qu.stage = 0; 
			break;
*/
	}

}

u8 quPackCount(void){
// количество элементов в очереди
	if (qu.head < qu.tail) {
		return (qu.tail-qu.head);
	} else {
		if (qu.head > qu.tail) {
			return qu.tail+quMaxItemCount-qu.head;
		} else {
			//if (qu.head == qu.tail)
			return 0;
		} 
	}
}

s8	quAddPack(u8 * buffer,u16 len,u8 transit){
// добавление пакета в очередь
	u16 i;
	// проверить есть ли место в очереди
	// Msg("%d \r\n",quPackCount());
	if (quPackCount() < (quMaxItemCount-1)) {
		i = qu.tail; // чтобы не таскать qu.tail
		//Dump(buffer,len);
		memcpy(qu.aqu[i].buf,buffer,len);
		qu.aqu[i].len = len;
		qu.aqu[i].repcount = *pQURepCount;
		qu.aqu[i].timeout = *pQUTimeout;
		qu.aqu[i].transit = transit;
		//Msg("ap %d %d\r\n",i,qu.aqu[i].buf[0]);
		qu.tail++;	// сдвигаем указатель на следующий свободный элемент
		qu.tail %= quMaxItemCount; // закольцовываем список
		//Msg("t %d\r\n",qu.tail);
		return 0;
	} else {
		// нет места
		Msg("dp %d\r\n",*buffer);
		if (*pDropCmd) {
			Msg("Drop Cmd ");
			Dump(buffer,len);
			Msg("\r\n");
		}
		return -1;
	}
}

s8	quInsPack(u8 * buffer,u16 len,u8 transit,u8 ofs){
// вставка пакета в очередь
	u16 i;
	if (ofs < 1) return -1;
	// проверить есть ли место в очереди
	// Msg("%d \r\n",quPackCount());
	if (quPackCount() < ofs+1) {
		// очередь пуста
		// просто добавляем пакет
		return quAddPack(buffer,len,transit);
	}
	// очередь не пуста
	// заменяем первый не обработанный пакет очереди на наш
	i = (qu.head+ofs) % quMaxItemCount; 
	//Dump(buffer,len);
	memcpy(qu.aqu[i].buf,buffer,len);
	qu.aqu[i].len = len;
	qu.aqu[i].repcount = *pQURepCount;
	qu.aqu[i].timeout = *pQUTimeout;
	qu.aqu[i].transit = transit;
	return 0;
}

void quFixAnswer(u8 * buffer,u16 len){
	u16 i;
	if (quPackCount() > 0) {
		i = qu.head; // чтобы не таскать qu.head
		memcpy(qu.aqu[i].qbuf,buffer,len);
		qu.aqu[i].qlen = len;
	}
}

// queue.c end
