#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "Defs.h"

#define cmDataToU1      	0x67

// максимальное количество пакетов в очереди
#define quMaxItemCount 30

// максимальная длина пакета
#define quMaxLenPack 	50
// транзитная и не транзитная команда
#define quCmdNoTransit 	0
#define quCmdTransit 	1

// тип элемента очереди
typedef struct tagTQUItem {
	u8 buf[quMaxLenPack]; 		// буфер команды
	u16 len;					// длина пакета
	u8 qbuf[quMaxLenPack];		// буфер квитанции
	u16 qlen;					// длина квитанции
	u8 repcount;				// количество повторов
	u16 timeout;				// timeout
	u8 transit;					// признак транзитной команды
} TQUItem;

// массив очереди
typedef TQUItem TAQueue[quMaxItemCount];

typedef struct tagTQueue {
	TAQueue aqu; 	// массив
	u16 head; 		// индекс головы
	u16 tail;		// индекс хвоста
	u8 stage;		// стадия работы очереди
} TQueue;

extern TQueue qu; // очередь


void InitQueue(void);
// инициализация очереди

void QueueProcessing(void);
// обработка очереди

s8	quAddPack(u8 * buffer,u16 len,u8 transit);
// добавление пакета в очередь

s8	quInsPack(u8 * buffer,u16 len,u8 transit,u8 ofs);
// вставка пакета в очередь

void quFixAnswer(u8 * buffer,u16 len);
// фиксирование буфере квитанции в очереди

u8 quPackCount(void);


#endif
