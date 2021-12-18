#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "Defs.h"

#define cmDataToU1      	0x67

// ������������ ���������� ������� � �������
#define quMaxItemCount 30

// ������������ ����� ������
#define quMaxLenPack 	50
// ���������� � �� ���������� �������
#define quCmdNoTransit 	0
#define quCmdTransit 	1

// ��� �������� �������
typedef struct tagTQUItem {
	u8 buf[quMaxLenPack]; 		// ����� �������
	u16 len;					// ����� ������
	u8 qbuf[quMaxLenPack];		// ����� ���������
	u16 qlen;					// ����� ���������
	u8 repcount;				// ���������� ��������
	u16 timeout;				// timeout
	u8 transit;					// ������� ���������� �������
} TQUItem;

// ������ �������
typedef TQUItem TAQueue[quMaxItemCount];

typedef struct tagTQueue {
	TAQueue aqu; 	// ������
	u16 head; 		// ������ ������
	u16 tail;		// ������ ������
	u8 stage;		// ������ ������ �������
} TQueue;

extern TQueue qu; // �������


void InitQueue(void);
// ������������� �������

void QueueProcessing(void);
// ��������� �������

s8	quAddPack(u8 * buffer,u16 len,u8 transit);
// ���������� ������ � �������

s8	quInsPack(u8 * buffer,u16 len,u8 transit,u8 ofs);
// ������� ������ � �������

void quFixAnswer(u8 * buffer,u16 len);
// ������������ ������ ��������� � �������

u8 quPackCount(void);


#endif
